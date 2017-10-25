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

#include "sm-pwm-01c/sm-pwm-01c.h"

int sm_pwm_01c_init(struct os_dev * dev, void * arg)
{
 return 1;
}

int sm_pwm_01c_config(struct sm_pwm_01c * dev, struct sm_pwm_01c_cfg * cfg)
{
    return 1;    
}
