/*
**   Copyright 2016 Telenor Digital AS
**
**  Licensed under the Apache License, Version 2.0 (the "License");
**  you may not use this file except in compliance with the License.
**  You may obtain a copy of the License at
**
**      http://www.apache.org/licenses/LICENSE-2.0
**
**  Unless required by applicable law or agreed to in writing, software
**  distributed under the License is distributed on an "AS IS" BASIS,
**  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**  See the License for the specific language governing permissions and
**  limitations under the License.
*/

#include <string.h>

#include "origin_gps/gps_std.h"
#include "origin_gps/gps_cache.h"
#include "os/os_arch.h"

static gps_fix_t gps_fix = {
	.timestamp = 0.0f,
	.latitude = 0.0f,
	.longitude = 0.0f,
	.altitude = 0.0f,
	.hdop = 0.0f,
	.vdop = 0.0f,
	.pdop = 0.0f,
	.fix_quality = FIX_Q_INVALID,
	.gps_svs = 0,
	.glo_svs = 0,
	.waas_svs = 0
};

bool gps_fix_is_valid(const gps_fix_t* fix) {
	return (fix != NULL && fix->fix_quality != FIX_Q_INVALID);
}

bool gps_get_fix(gps_fix_t* fix) {

    int sr;
	OS_ENTER_CRITICAL(sr);
	memcpy(fix, &gps_fix, sizeof(gps_fix_t));
    OS_EXIT_CRITICAL(sr);

	return gps_fix_is_valid(fix);
}

void gps_update_gga(gps_gga_t* gga) {
	if (gga->fix_quality == FIX_Q_INVALID) {
		return;
	}

    int sr;
	OS_ENTER_CRITICAL(sr);
	gps_fix.timestamp = gga->timestamp;
	gps_fix.latitude = gga->latitude;
	gps_fix.longitude = gga->longitude;
	gps_fix.altitude = gga->alt;
	gps_fix.fix_quality = gga->fix_quality;
	gps_fix.hdop = gga->hdop;
    OS_EXIT_CRITICAL(sr);
}

void gps_update_gsa(gps_gsa_t* gsa) {
    int sr;
	OS_ENTER_CRITICAL(sr);
	gps_fix.vdop = gsa->vdop;
	gps_fix.pdop = gsa->pdop;

	// Do some guesswork to determine which satellites are in use:
	// - GPS has PRNs 1-32
	// - WAAS (EGNOS) has PRNs 33-64
	// - GLONASS has PRNs 65-96
	uint8_t gps_prns = 0;
	uint8_t glo_prns = 0;
	uint8_t waas_prns = 0;

	for (int i = 0; i < MAX_GSA_PRNS; i++) {
		if (gsa->prns[i] == 0) {
			continue;
		}
		if (gsa->prns[i] <= 32) {
			gps_prns++;
		}
		else if (gsa->prns[i] <= 64) {
			waas_prns++;

		} else if (gsa->prns[i] <= 96) {
			glo_prns++;
		}
	}

	if (gps_prns > 0) {
		gps_fix.gps_svs = gps_prns;
	}

	if (waas_prns > 0) {
		gps_fix.waas_svs = waas_prns;
	}

	if (glo_prns > 0) {
		gps_fix.glo_svs = glo_prns;
	}
    OS_EXIT_CRITICAL(sr);
}

static gps_fix_stats_t stats = {
	.max_time = 0,
	.min_time = 0xFF,
	.last_time = 0,
	.samples = 0,
	.total_time = 0,
	.timeouts = 0
};

void gps_add_fix_stat(const int seconds_to_fix) {
    int sr;
	OS_ENTER_CRITICAL(sr);
	if (seconds_to_fix < stats.min_time) {
		stats.min_time = seconds_to_fix;
	}
	if (seconds_to_fix > stats.max_time) {
		stats.max_time = seconds_to_fix;
	}
	stats.samples++;
	stats.total_time += seconds_to_fix;
	stats.last_time = seconds_to_fix;
    OS_EXIT_CRITICAL(sr);
}

void gps_add_timeout_stat() {
    int sr;
	OS_ENTER_CRITICAL(sr);
	stats.timeouts++;
    OS_EXIT_CRITICAL(sr);
}

/**
 * Get fix statistics
 */
void gps_get_fix_stat(gps_fix_stats_t* statcp) {
    int sr;
	OS_ENTER_CRITICAL(sr);
	memcpy(statcp, &stats, sizeof(gps_fix_stats_t));
    OS_EXIT_CRITICAL(sr);
}

void gps_reset_cache(void) {
    int sr;
	OS_ENTER_CRITICAL(sr);
	gps_fix.timestamp = 0;
	gps_fix.latitude = 0;
	gps_fix.longitude = 0;
	gps_fix.fix_quality = FIX_Q_INVALID;
    OS_EXIT_CRITICAL(sr);
}

static imu_data_t imu_data = {
	.accel_x = 0.0f,
	.accel_y = 0.0f,
	.accel_z = 0.0f,
	.temperature = 0.0f
};

void imu_update_accel(float x, float y, float z) {
    int sr;
	OS_ENTER_CRITICAL(sr);
	imu_data.accel_x = x;
	imu_data.accel_y = y;
	imu_data.accel_z = z;
    OS_EXIT_CRITICAL(sr);
}

void imu_update_temp(float temperature) {
    int sr;
	OS_ENTER_CRITICAL(sr);
	imu_data.temperature = temperature;
    OS_EXIT_CRITICAL(sr);
}

void imu_update_mag(float x, float y, float z) {
    int sr;
	OS_ENTER_CRITICAL(sr);
	imu_data.mag_x = x;
	imu_data.mag_y = y;
	imu_data.mag_z = z;
    OS_EXIT_CRITICAL(sr);
}

void imu_get_data(imu_data_t* data) {
    int sr;
	OS_ENTER_CRITICAL(sr);
	memcpy(data, &imu_data, sizeof(imu_data_t));
    OS_EXIT_CRITICAL(sr);
}
