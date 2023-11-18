/**************************************************************************************************
 * @file   RenderingTestsHelper.h
 * @author Valentin Dumitru
 * @date   2023-11-09
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <SDL2/SDL.h>

#define LOOP_FRAMES 2


#define LOOP() \
    for (int i = 0; i < LOOP_FRAMES; i++)