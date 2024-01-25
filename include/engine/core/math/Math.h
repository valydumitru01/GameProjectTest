/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include <cmath>
#include <type_traits>
#include <random>
#include "engine/core/asserts/Asserts.h"


namespace GLESC::Math {
    // TODO: Implement min and max and limit functions
    constexpr float FLOAT_COMPARISON_EPSILON = 1e-6f;
    constexpr double DOUBLE_COMPARISON_EPSILON = 1e-10;

    constexpr float PI          = 3.1415926;            // 7 digits of precision
    constexpr double PI_DOUBLE  = 3.1415926535897932;   // 16 digits of precision
    
    template<typename Type>
    constexpr Type pi() {
        if constexpr (std::is_same_v<Type, float>)
            return PI;
        else if constexpr (std::is_same_v<Type, double>)
            return PI_DOUBLE;
        else
            static_assert(std::is_floating_point_v<Type>,
                    "PI is only defined for floating point types");
    }
    
    template<typename Type>
    constexpr inline auto epsilon() {
        using DecayedType = std::remove_const_t<std::remove_reference_t<Type>>;
        if constexpr (std::is_same_v<DecayedType, float>) {
            return FLOAT_COMPARISON_EPSILON;
        } else if constexpr (std::is_same_v<DecayedType, double>) {
            return DOUBLE_COMPARISON_EPSILON;
        } else {
            // Handle other floating point types
            return DecayedType(1e-7);
        }
    }
    
    template <typename Type>
    constexpr inline Type epsilon(Type value) {
        return epsilon<Type>() * flexibleAbs(value);
    }
    
    template<typename Type>
    Type radians(const Type &degrees) {
        return degrees * PI / Type(180);
    }
    
    template<typename Type>
    Type degrees(const Type &radians) {
        return radians * Type(180) / PI;
    }
    
    
    template<typename LValueT, typename RValueT>
    constexpr inline bool eq(LValueT a, RValueT b) {
        if constexpr (std::is_floating_point_v<LValueT> && std::is_floating_point_v<RValueT>) {
            // Determine the type with the lower precision
            using LowerPrecisionType = std::conditional_t<
                    (sizeof(LValueT) < sizeof(RValueT)), LValueT, RValueT>;
            
            // Use the epsilon of the type with the lower precision
            constexpr auto epsilon = GLESC::Math::epsilon<LowerPrecisionType>();
            return std::fabs(a - b) < epsilon;
        } else {
            return a == b;
        }
    }
    
    template<typename Type>
    constexpr inline Type abs(Type value) {
        if constexpr (std::is_floating_point_v<Type>) {
            return std::fabs(value);
        } else if constexpr (std::is_unsigned_v<Type>){
            return value;
        } else if constexpr (std::is_arithmetic_v<Type> && std::is_signed_v<Type>) {
            return std::abs(value);
        } else {
            // For user-defined types, you might want to call a member function
            // or free function that computes the absolute value for that type.
            // For demonstration, let's assume T has a member function abs() that
            // computes the absolute value:
            return value.absol();
        }
    }
    
    template <typename T>
    T sqrt(const T& value) {
        T result = T();
        if constexpr (std::is_arithmetic_v<T>) {
            if constexpr (std::is_integral_v<T>) {
                return static_cast<T>(std::round(std::sqrt(static_cast<double>(value))));
            } else {
                return static_cast<T>(std::sqrt(value));
            }
        } else {
            // For user-defined types, you might want to call a member function
            // or free function that computes the square root for that type.
            // For demonstration, let's assume T has a member function sqrt() that
            // computes the square root:
            result = value.sqrt();
        }
        return result;
    }
    
    template<typename Type>
    Type generateRandomNumber(Type min, Type max) {
        S_ASSERT_TRUE(std::is_arithmetic_v<Type>, "Type must be arithmetic");
        static std::random_device rd;
        static std::mt19937 mt(rd());
        
        // If the type is uint, we use the fast unsigned int type for the distribution
        if constexpr (std::is_unsigned_v<Type> && std::is_integral_v<Type>) {
            std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
            return dist(mt);
        }
        // If the type is int, we just use the int type for the int distribution
        else if constexpr (std::is_integral_v<Type>) {
            std::uniform_int_distribution<Type> dist(min, max);
            return dist(mt);
        }
        
        // If the type is floating point, we use the real distribution and we decrease the max value
        else if constexpr (std::is_floating_point_v<Type>) {
            // Prevent the generation of infinity by reducing the max value by the smallest possible amount
            // in the direction of the min value
            Type safeMax = std::nextafter(max, std::numeric_limits<Type>::lowest());
            std::uniform_real_distribution<Type> dist(min, safeMax);
            return dist(mt);
        }
        
        // If the type is not integral or floating point, we don't know how to generate a random number
        else {
            static_assert(std::is_arithmetic_v<Type>, "Unsupported type for generateRandomNumber");
        }
    }
    
    template<typename Type>
    Type generateRandomNumber() {
        return generateRandomNumber(std::numeric_limits<Type>::lowest(), std::numeric_limits<Type>::max());
    }
    

}

