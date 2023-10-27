/******************************************************************************
 * @file   VectorTest.cpp
 * @author Valentin Dumitru
 * @date   2023-10-06
 * @brief  @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#include <gtest/gtest.h>
#include "engine/core/math/Math.h"
#include "engine/core/math/Vec.h"


using namespace GLESC::Math;
// ------------------------ Constructor Tests ------------------------ //
TEST(VectorTests, DefaultConstructor) {
    Vec<Vec<int, 2>, 2> vec2X2;
    EXPECT_EQ(vec2X2[0][0], 0);
    EXPECT_EQ(vec2X2[0][1], 0);
    EXPECT_EQ(vec2X2[1][0], 0);
    EXPECT_EQ(vec2X2[1][1], 0);
    
    Vec<int, 2> vecI;
    EXPECT_EQ(vecI[0], 0);
    EXPECT_EQ(vecI[1], 0);
    
    Vec<float, 3> vecF;
    EXPECT_FLOAT_EQ(vecF[0], 0);
    EXPECT_FLOAT_EQ(vecF[1], 0);
    EXPECT_FLOAT_EQ(vecF[2], 0);
    
    Vec<size_t, 4> vecSt;
    EXPECT_EQ(vecSt[0], 0);
    EXPECT_EQ(vecSt[1], 0);
    EXPECT_EQ(vecSt[2], 0);
    EXPECT_EQ(vecSt[3], 0);
}

TEST(VectorTests, FillConstructor) {
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1));
    auto expected1 = Vec<int, 2>(1);
    auto expected2 = Vec<int, 2>(1);
    EXPECT_EQ(vec2X2[0], expected1);
    EXPECT_EQ(vec2X2[1], expected2);
    
    Vec<int, 2> vecI(1);
    EXPECT_EQ(vecI[0], 1);
    EXPECT_EQ(vecI[1], 1);
    
    Vec<float, 3> vecF(1.0);
    EXPECT_FLOAT_EQ(vecF[0], 1.0);
    EXPECT_FLOAT_EQ(vecF[1], 1.0);
    EXPECT_FLOAT_EQ(vecF[2], 1.0);
    
    Vec<size_t, 4> vecSt(1);
    EXPECT_EQ(vecSt[0], 1);
    EXPECT_EQ(vecSt[1], 1);
    EXPECT_EQ(vecSt[2], 1);
    EXPECT_EQ(vecSt[3], 1);
}

TEST(VectorTests, ParametrizedConstructor) {
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    EXPECT_EQ(vec2X2[0][0], 1);
    EXPECT_EQ(vec2X2[0][1], 2);
    EXPECT_EQ(vec2X2[1][0], 3);
    EXPECT_EQ(vec2X2[1][1], 4);
    
    Vec<int, 2> vecI(1, 2);
    EXPECT_EQ(vecI[0], 1);
    EXPECT_EQ(vecI[1], 2);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    EXPECT_FLOAT_EQ(vecF[0], 1);
    EXPECT_FLOAT_EQ(vecF[1], 2);
    EXPECT_FLOAT_EQ(vecF[2], 3);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    EXPECT_EQ(vecSt[0], 1);
    EXPECT_EQ(vecSt[1], 2);
    EXPECT_EQ(vecSt[2], 3);
    EXPECT_EQ(vecSt[3], 4);
}

TEST(VectorTests, CopyConstructor) {
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    Vec<Vec<int, 2>, 2> vec2X22(vec2X2); // NOLINT
    EXPECT_EQ(vec2X22[0][0], vec2X2[0][0]);
    EXPECT_EQ(vec2X22[0][1], vec2X2[0][1]);
    EXPECT_EQ(vec2X22[1][0], vec2X2[1][0]);
    EXPECT_EQ(vec2X22[1][1], vec2X2[1][1]);
    
    Vec<int, 2> vecI(1, 2);
    Vec<int, 2> vecI2(vecI); // NOLINT
    EXPECT_EQ(vecI2[0], vecI[0]);
    EXPECT_EQ(vecI2[1], vecI[1]);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    Vec<float, 3> vecF2(vecF); // NOLINT
    EXPECT_FLOAT_EQ(vecF2[0], vecF[0]);
    EXPECT_FLOAT_EQ(vecF2[1], vecF[1]);
    EXPECT_FLOAT_EQ(vecF2[2], vecF[2]);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    Vec<size_t, 4> vecSt2(vecSt); // NOLINT
    EXPECT_EQ(vecSt2[0], vecSt[0]);
    EXPECT_EQ(vecSt2[1], vecSt[1]);
    EXPECT_EQ(vecSt2[2], vecSt[2]);
    EXPECT_EQ(vecSt2[3], vecSt[3]);
}

TEST(VectorTests, MoveConstructor) {
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    Vec<Vec<int, 2>, 2> vec2X22(std::move(vec2X2));
    EXPECT_EQ(vec2X22[0][0], 1);
    EXPECT_EQ(vec2X22[0][1], 2);
    EXPECT_EQ(vec2X22[1][0], 3);
    EXPECT_EQ(vec2X22[1][1], 4);
    
    Vec<int, 2> vecI(1, 2); // Becomes invalid after move (undefined behavior)
    Vec<int, 2> vecI2(std::move(vecI));
    EXPECT_EQ(vecI2[0], 1);
    EXPECT_EQ(vecI2[1], 2);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0); // Becomes invalid after move (undefined behavior)
    Vec<float, 3> vecF2(std::move(vecF));
    EXPECT_FLOAT_EQ(vecF2[0], 1);
    EXPECT_FLOAT_EQ(vecF2[1], 2);
    EXPECT_FLOAT_EQ(vecF2[2], 3);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4); // Becomes invalid after move (undefined behavior)
    Vec<size_t, 4> vecSt2(std::move(vecSt));
    EXPECT_EQ(vecSt2[0], 1);
    EXPECT_EQ(vecSt2[1], 2);
    EXPECT_EQ(vecSt2[2], 3);
    EXPECT_EQ(vecSt2[3], 4);
}

TEST(VectorTests, InitializerListConstructor) {
    Vec<Vec<int, 2>, 2> vec2X2({Vec<int, 2>({1, 2}), Vec<int, 2>({3, 4})});
    EXPECT_EQ(vec2X2[0][0], 1);
    EXPECT_EQ(vec2X2[0][1], 2);
    EXPECT_EQ(vec2X2[1][0], 3);
    EXPECT_EQ(vec2X2[1][1], 4);
    
    Vec<int, 2> vecI({1, 2});
    EXPECT_EQ(vecI[0], 1);
    EXPECT_EQ(vecI[1], 2);
    
    Vec<float, 3> vecF({1.0, 2.0, 3.0});
    EXPECT_FLOAT_EQ(vecF[0], 1);
    EXPECT_FLOAT_EQ(vecF[1], 2);
    EXPECT_FLOAT_EQ(vecF[2], 3);
    
    Vec<size_t, 4> vecSt({1, 2, 3, 4});
    EXPECT_EQ(vecSt[0], 1);
    EXPECT_EQ(vecSt[1], 2);
    EXPECT_EQ(vecSt[2], 3);
    EXPECT_EQ(vecSt[3], 4);
}

TEST(VectorTests, ParametrizedConstructorNarrowerNumber) {
    Vec<double, 2> vecI(1.0f, 2.0f);
    EXPECT_FLOAT_EQ(vecI[0], 1.0);
    EXPECT_FLOAT_EQ(vecI[1], 2.0);
    
    Vec<double, 3> vecF(1.0f, 2u, 3.0f);
    EXPECT_FLOAT_EQ(vecF[0], 1.0);
    EXPECT_FLOAT_EQ(vecF[1], 2.0);
    EXPECT_FLOAT_EQ(vecF[2], 3.0);
    
    Vec<double, 4> vecSt(1.03f, 2, 3u, 4);
    EXPECT_FLOAT_EQ(vecSt[0], 1.03);
    EXPECT_FLOAT_EQ(vecSt[1], 2.0);
    EXPECT_FLOAT_EQ(vecSt[2], 3.0);
    EXPECT_FLOAT_EQ(vecSt[3], 4.0);
}


TEST(VectorTests, FillConstructorNarrowerNumber) {
    Vec<double, 2> vecI(1.0f);
    EXPECT_FLOAT_EQ(vecI[0], 1.0);
    EXPECT_FLOAT_EQ(vecI[1], 1.0);
    
    Vec<double, 3> vecF(1u);
    EXPECT_FLOAT_EQ(vecF[0], 1.0);
    EXPECT_FLOAT_EQ(vecF[1], 1.0);
    EXPECT_FLOAT_EQ(vecF[2], 1.0);
    
    Vec<double, 4> vecSt(1.03f);
    EXPECT_FLOAT_EQ(vecSt[0], 1.03);
    EXPECT_FLOAT_EQ(vecSt[1], 1.03);
    EXPECT_FLOAT_EQ(vecSt[2], 1.03);
    EXPECT_FLOAT_EQ(vecSt[3], 1.03);
}

TEST(VectorTests, CopyConstructorNarrowerNumber) {
    Vec<double, 2> vecI(1.0f, 2.0f);
    Vec<double, 2> vecI2(vecI); // NOLINT
    EXPECT_FLOAT_EQ(vecI2[0], 1.0);
    EXPECT_FLOAT_EQ(vecI2[1], 2.0);
    
    Vec<double, 3> vecF(1.0f, 2u, 3.0f);
    Vec<double, 3> vecF2(vecF); // NOLINT
    EXPECT_FLOAT_EQ(vecF2[0], 1.0);
    EXPECT_FLOAT_EQ(vecF2[1], 2.0);
    EXPECT_FLOAT_EQ(vecF2[2], 3.0);
    
    Vec<double, 4> vecSt(1.03f, 2, 3u, 4);
    Vec<double, 4> vecSt2(vecSt); // NOLINT
    EXPECT_FLOAT_EQ(vecSt2[0], 1.03);
    EXPECT_FLOAT_EQ(vecSt2[1], 2.0);
    EXPECT_FLOAT_EQ(vecSt2[2], 3.0);
    EXPECT_FLOAT_EQ(vecSt2[3], 4.0);
}

TEST(VectorTests, MoveConstructorNarrowerNumber) {
    Vec<double, 2> vecI(1.0f, 2.0f);
    Vec<double, 2> vecI2(std::move(vecI));
    EXPECT_FLOAT_EQ(vecI2[0], 1.0);
    EXPECT_FLOAT_EQ(vecI2[1], 2.0);
    
    Vec<double, 3> vecF(1.0f, 2u, 3.0f);
    Vec<double, 3> vecF2(std::move(vecF));
    EXPECT_FLOAT_EQ(vecF2[0], 1.0);
    EXPECT_FLOAT_EQ(vecF2[1], 2.0);
    EXPECT_FLOAT_EQ(vecF2[2], 3.0);
    
    Vec<double, 4> vecSt(1.03f, 2, 3u, 4);
    Vec<double, 4> vecSt2(std::move(vecSt));
    EXPECT_FLOAT_EQ(vecSt2[0], 1.03);
    EXPECT_FLOAT_EQ(vecSt2[1], 2.0);
    EXPECT_FLOAT_EQ(vecSt2[2], 3.0);
    EXPECT_FLOAT_EQ(vecSt2[3], 4.0);
}

TEST(VectorTests, InitializerListConstructorNarrowerNumber) {
    Vec<double, 2> vecI({1.0f, 2.0f});
    EXPECT_FLOAT_EQ(vecI[0], 1.0);
    EXPECT_FLOAT_EQ(vecI[1], 2.0);
    
    Vec<double, 3> vecF({1.0f, 2u, 3.0f});
    EXPECT_FLOAT_EQ(vecF[0], 1.0);
    EXPECT_FLOAT_EQ(vecF[1], 2.0);
    EXPECT_FLOAT_EQ(vecF[2], 3.0);
    
    Vec<double, 4> vecSt({1.03f, 2, 3u, 4});
    EXPECT_FLOAT_EQ(vecSt[0], 1.03);
    EXPECT_FLOAT_EQ(vecSt[1], 2.0);
    EXPECT_FLOAT_EQ(vecSt[2], 3.0);
    EXPECT_FLOAT_EQ(vecSt[3], 4.0);
}


// ------------------------ Access Tests ------------------------ //

TEST(VectorTests, AccessOperator) {
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    EXPECT_EQ(vec2X2[0][0], 1);
    EXPECT_EQ(vec2X2[0][1], 2);
    EXPECT_EQ(vec2X2[1][0], 3);
    EXPECT_EQ(vec2X2[1][1], 4);
    
    Vec<int, 2> vecI(1, 2);
    EXPECT_EQ(vecI[0], 1);
    EXPECT_EQ(vecI[1], 2);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    EXPECT_FLOAT_EQ(vecF[0], 1);
    EXPECT_FLOAT_EQ(vecF[1], 2);
    EXPECT_FLOAT_EQ(vecF[2], 3);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    EXPECT_EQ(vecSt[0], 1);
    EXPECT_EQ(vecSt[1], 2);
    EXPECT_EQ(vecSt[2], 3);
    EXPECT_EQ(vecSt[3], 4);
}

TEST(VectorTests, ConstAccessOperator) {
    const Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    EXPECT_EQ(vec2X2[0][0], 1);
    EXPECT_EQ(vec2X2[0][1], 2);
    EXPECT_EQ(vec2X2[1][0], 3);
    EXPECT_EQ(vec2X2[1][1], 4);
    
    const Vec<int, 2> vecI(1, 2);
    EXPECT_EQ(vecI[0], 1);
    EXPECT_EQ(vecI[1], 2);
    
    const Vec<float, 3> vecF(1.0, 2.0, 3.0);
    EXPECT_FLOAT_EQ(vecF[0], 1);
    EXPECT_FLOAT_EQ(vecF[1], 2);
    EXPECT_FLOAT_EQ(vecF[2], 3);
    
    const Vec<size_t, 4> vecSt(1, 2, 3, 4);
    EXPECT_EQ(vecSt[0], 1);
    EXPECT_EQ(vecSt[1], 2);
    EXPECT_EQ(vecSt[2], 3);
    EXPECT_EQ(vecSt[3], 4);
}

TEST(VectorTests, Getter) {
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    auto expected1 = Vec<int, 2>(1, 2);
    auto expected2 = Vec<int, 2>(3, 4);
    EXPECT_EQ(vec2X2.getX(), expected1);
    EXPECT_EQ(vec2X2.getY(), expected2);
    
    Vec<int, 2> vecI(1, 2);
    EXPECT_EQ(vecI.getX(), 1);
    EXPECT_EQ(vecI.getY(), 2);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    EXPECT_FLOAT_EQ(vecF.getX(), 1);
    EXPECT_FLOAT_EQ(vecF.getY(), 2);
    EXPECT_FLOAT_EQ(vecF.getZ(), 3);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    EXPECT_EQ(vecSt.getX(), 1);
    EXPECT_EQ(vecSt.getY(), 2);
    EXPECT_EQ(vecSt.getZ(), 3);
    EXPECT_EQ(vecSt.getW(), 4);
}

TEST(VectorTests, ShortGetter) {
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    auto expected1 = Vec<int, 2>(1, 2);
    auto expected2 = Vec<int, 2>(3, 4);
    EXPECT_EQ(vec2X2.x(), expected1);
    EXPECT_EQ(vec2X2.y(), expected2);
    
    Vec<int, 2> vecI(1, 2);
    EXPECT_EQ(vecI.x(), 1);
    EXPECT_EQ(vecI.y(), 2);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    EXPECT_FLOAT_EQ(vecF.x(), 1);
    EXPECT_FLOAT_EQ(vecF.y(), 2);
    EXPECT_FLOAT_EQ(vecF.z(), 3);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    EXPECT_EQ(vecSt.x(), 1);
    EXPECT_EQ(vecSt.y(), 2);
    EXPECT_EQ(vecSt.z(), 3);
    EXPECT_EQ(vecSt.w(), 4);
    
    // vecI.z(); // Should not compile
    // vecI.w(); // Should not compile (only for 4D vectors)
    
}

TEST(VectorTests, Setter) {
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    vec2X2.setX(Vec<int, 2>(3, 4));
    vec2X2.setY(Vec<int, 2>(1, 2));
    auto expected1 = Vec<int, 2>(3, 4);
    auto expected2 = Vec<int, 2>(1, 2);
    EXPECT_EQ(vec2X2.getX(), expected1);
    EXPECT_EQ(vec2X2.getY(), expected2);
    
    Vec<int, 2> vecI(1, 2);
    vecI.setX(3);
    vecI.setY(4);
    EXPECT_EQ(vecI.getX(), 3);
    EXPECT_EQ(vecI.getY(), 4);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    vecF.setX(3);
    vecF.setY(4);
    vecF.setZ(5);
    EXPECT_FLOAT_EQ(vecF.getX(), 3.0);
    EXPECT_FLOAT_EQ(vecF.getY(), 4.0);
    EXPECT_FLOAT_EQ(vecF.getZ(), 5.0);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    vecSt.setX(3);
    vecSt.setY(4);
    vecSt.setZ(5);
    vecSt.setW(6);
    EXPECT_EQ(vecSt.getX(), 3);
    EXPECT_EQ(vecSt.getY(), 4);
    EXPECT_EQ(vecSt.getZ(), 5);
    EXPECT_EQ(vecSt.getW(), 6);
    
    // Narrower number
    Vec<int, 2> vecI2(1, 2);
    vecI2.setX(3.0f);
    vecI2.setY(4.0f);
}

// ---------------------------------------------------------------- //
// ------------------------ Operator Tests ------------------------ //
// ---------------------------------------------------------------- //

// ------------------ Assignment Operators Tests ------------------ //

TEST(VectorTests, AssignmentOperator) {
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    Vec<Vec<int, 2>, 2> vec2X22;
    vec2X22 = vec2X2;
    EXPECT_EQ(vec2X22[0][0], 1);
    EXPECT_EQ(vec2X22[0][1], 2);
    EXPECT_EQ(vec2X22[1][0], 3);
    EXPECT_EQ(vec2X22[1][1], 4);
    
    Vec<int, 2> vecI(1, 2);
    Vec<int, 2> vecI2;
    vecI2 = vecI;
    EXPECT_EQ(vecI2[0], 1);
    EXPECT_EQ(vecI2[1], 2);
    
    EXPECT_EQ(vecI[0], 1);
    EXPECT_EQ(vecI[1], 2);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    Vec<float, 3> vecF2;
    vecF2 = vecF;
    EXPECT_FLOAT_EQ(vecF2[0], 1);
    EXPECT_FLOAT_EQ(vecF2[1], 2);
    EXPECT_FLOAT_EQ(vecF2[2], 3);
    
    EXPECT_FLOAT_EQ(vecF[0], 1);
    EXPECT_FLOAT_EQ(vecF[1], 2);
    EXPECT_FLOAT_EQ(vecF[2], 3);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    Vec<size_t, 4> vecSt2;
    vecSt2 = vecSt;
    EXPECT_EQ(vecSt2[0], 1);
    EXPECT_EQ(vecSt2[1], 2);
    EXPECT_EQ(vecSt2[2], 3);
    EXPECT_EQ(vecSt2[3], 4);
    
    EXPECT_EQ(vecSt[0], 1);
    EXPECT_EQ(vecSt[1], 2);
    EXPECT_EQ(vecSt[2], 3);
    EXPECT_EQ(vecSt[3], 4);
    
    // Narrower number
    Vec<int, 2> vecI3(1, 2);
    Vec<double, 2> vecI4;
}

TEST(VectorTests, MoveAssignmentOperator) {
    // Becomes invalid after move (undefined behavior)
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    Vec<Vec<int, 2>, 2> vec2X22;
    vec2X22 = std::move(vec2X2);
    EXPECT_EQ(vec2X22[0][0], 1);
    EXPECT_EQ(vec2X22[0][1], 2);
    EXPECT_EQ(vec2X22[1][0], 3);
    EXPECT_EQ(vec2X22[1][1], 4);
    
    Vec<int, 2> vecI(1, 2); // Becomes invalid after move (undefined behavior)
    Vec<int, 2> vecI2;
    vecI2 = std::move(vecI);
    EXPECT_EQ(vecI2[0], 1);
    EXPECT_EQ(vecI2[1], 2);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0); // Becomes invalid after move (undefined behavior)
    Vec<float, 3> vecF2;
    vecF2 = std::move(vecF);
    EXPECT_FLOAT_EQ(vecF2[0], 1);
    EXPECT_FLOAT_EQ(vecF2[1], 2);
    EXPECT_FLOAT_EQ(vecF2[2], 3);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4); // Becomes invalid after move (undefined behavior)
    Vec<size_t, 4> vecSt2;
    vecSt2 = std::move(vecSt);
    EXPECT_EQ(vecSt2[0], 1);
    EXPECT_EQ(vecSt2[1], 2);
    EXPECT_EQ(vecSt2[2], 3);
    EXPECT_EQ(vecSt2[3], 4);
    
    // Narrower number
    Vec<int, 2> vecI3(1, 2);
    Vec<double, 2> vecI4;
}

TEST(VectorTests, CopyAssignmentOperator) {
    Vec<double, 2> vecI(1.0f, 2.0f);
    Vec<double, 2> vecI2;
    vecI2 = vecI; // NOLINT
    EXPECT_FLOAT_EQ(vecI2[0], vecI[0]);
    EXPECT_FLOAT_EQ(vecI2[1], vecI[1]);
    
    Vec<double, 3> vecF(1.0f, 2u, 3.0f);
    Vec<double, 3> vecF2;
    vecF2 = vecF; // NOLINT
    EXPECT_FLOAT_EQ(vecF2[0], vecF[0]);
    EXPECT_FLOAT_EQ(vecF2[1], vecF[1]);
    EXPECT_FLOAT_EQ(vecF2[2], vecF[2]);
    
    // Narrower number
    Vec<int, 4> vecSt(1, 2, 3, 4);
    Vec<double, 4> vecSt2;
    
}

TEST(VectorTests, AdditionAssignmentOperator) {
    Vec<double, 2> vecI(1.0, 2.0);
    Vec<double, 2> vecI2(1.0, 2.0);
    vecI += vecI2;
    EXPECT_FLOAT_EQ(vecI[0], 2.0);
    EXPECT_FLOAT_EQ(vecI[1], 4.0);
    
    Vec<double, 3> vecF(1.0, 2.0, 3.0);
    Vec<double, 3> vecF2(1.0, 2.0, 3.0);
    vecF += vecF2;
    EXPECT_FLOAT_EQ(vecF[0], 2.0);
    EXPECT_FLOAT_EQ(vecF[1], 4.0);
    EXPECT_FLOAT_EQ(vecF[2], 6.0);
    
    Vec<double, 4> vecSt(1.03, 2.0, 3.0, 4.0);
    Vec<double, 4> vecSt2(1.03, 2.0, 3.0, 4.0);
    vecSt += vecSt2;
    EXPECT_FLOAT_EQ(vecSt[0], 2.06);
    EXPECT_FLOAT_EQ(vecSt[1], 4.0);
    EXPECT_FLOAT_EQ(vecSt[2], 6.0);
    EXPECT_FLOAT_EQ(vecSt[3], 8.0);
    
    Vec<double, 2> vecI3(1.0, 2.0);
    vecI3 += 2.0;
    EXPECT_FLOAT_EQ(vecI3[0], 3.0);
    EXPECT_FLOAT_EQ(vecI3[1], 4.0);
    
    // Narrower number
    Vec<double, 2> vecI4(1.0, 2.0);
    vecI4 += 2;
    EXPECT_FLOAT_EQ(vecI4[0], 3.0);
    EXPECT_FLOAT_EQ(vecI4[1], 4.0);
}

TEST(VectorTests, SubstractionAssignmentOperator) {
    Vec<double, 2> vecI(1.0, 2.0);
    Vec<double, 2> vecI2(1.0, 2.0);
    vecI -= vecI2;
    EXPECT_FLOAT_EQ(vecI[0], 0.0);
    EXPECT_FLOAT_EQ(vecI[1], 0.0);
    
    Vec<double, 3> vecF(1.0, 2.0, 3.0);
    Vec<double, 3> vecF2(1.0, 2.0, 3.0);
    vecF -= vecF2;
    EXPECT_FLOAT_EQ(vecF[0], 0.0);
    EXPECT_FLOAT_EQ(vecF[1], 0.0);
    EXPECT_FLOAT_EQ(vecF[2], 0.0);
    
    Vec<double, 4> vecSt(1.03, 2.0, 3.0, 4.0);
    Vec<double, 4> vecSt2(1.03, 2.0, 3.0, 4.0);
    vecSt -= vecSt2;
    EXPECT_FLOAT_EQ(vecSt[0], 0.0);
    EXPECT_FLOAT_EQ(vecSt[1], 0.0);
    EXPECT_FLOAT_EQ(vecSt[2], 0.0);
    EXPECT_FLOAT_EQ(vecSt[3], 0.0);
    
    Vec<double, 2> vecI3(1.0, 2.0);
    vecI3 -= 2.0;
    EXPECT_FLOAT_EQ(vecI3[0], -1.0);
    EXPECT_FLOAT_EQ(vecI3[1], 0.0);
    
    // Narrower number
    Vec<double, 2> vecI4(1.0, 2.0);
    vecI4 -= 2;
    EXPECT_FLOAT_EQ(vecI4[0], -1.0);
    EXPECT_FLOAT_EQ(vecI4[1], 0.0);
}

TEST(VectorTests, MultiplicationAssignmentOperator) {
    Vec<double, 2> vecI(1.0, 2.0);
    Vec<double, 2> vecI2(1.0, 2.0);
    vecI *= vecI2;
    EXPECT_FLOAT_EQ(vecI[0], 1.0);
    EXPECT_FLOAT_EQ(vecI[1], 4.0);
    
    Vec<double, 3> vecF(1.0, 2.0, 3.0);
    Vec<double, 3> vecF2(1.0, 2.0, 3.0);
    vecF *= vecF2;
    EXPECT_FLOAT_EQ(vecF[0], 1.0);
    EXPECT_FLOAT_EQ(vecF[1], 4.0);
    EXPECT_FLOAT_EQ(vecF[2], 9.0);
    
    Vec<double, 4> vecSt(1.03, 2.0, 3.0, 4.0);
    Vec<double, 4> vecSt2(1.03, 2.0, 3.0, 4.0);
    vecSt *= vecSt2;
    EXPECT_FLOAT_EQ(vecSt[0], 1.0609);
    EXPECT_FLOAT_EQ(vecSt[1], 4.0);
    EXPECT_FLOAT_EQ(vecSt[2], 9.0);
    EXPECT_FLOAT_EQ(vecSt[3], 16.0);
    
    Vec<double, 2> vecI3(1.0, 2.0);
    vecI3 *= 2.0;
    EXPECT_FLOAT_EQ(vecI3[0], 2.0);
    EXPECT_FLOAT_EQ(vecI3[1], 4.0);
    
    // Narrower number
    Vec<double, 2> vecI4(1.0, 2.0);
    vecI4 *= 2;
    EXPECT_FLOAT_EQ(vecI4[0], 2.0);
    EXPECT_FLOAT_EQ(vecI4[1], 4.0);
}

TEST(VectorTests, DivisionAssignmentOperator) {
    Vec<double, 2> vecI(1.0, 2.0);
    Vec<double, 2> vecI2(1.0, 2.0);
    vecI /= vecI2;
    EXPECT_FLOAT_EQ(vecI[0], 1.0);
    EXPECT_FLOAT_EQ(vecI[1], 1.0);
    
    Vec<double, 3> vecF(1.0, 2.0, 3.0);
    Vec<double, 3> vecF2(1.0, 2.0, 3.0);
    vecF /= vecF2;
    EXPECT_FLOAT_EQ(vecF[0], 1.0);
    EXPECT_FLOAT_EQ(vecF[1], 1.0);
    EXPECT_FLOAT_EQ(vecF[2], 1.0);
    
    Vec<double, 4> vecSt(1.03, 2.0, 3.0, 4.0);
    Vec<double, 4> vecSt2(1.03, 2.0, 3.0, 4.0);
    vecSt /= vecSt2;
    EXPECT_FLOAT_EQ(vecSt[0], 1.0);
    EXPECT_FLOAT_EQ(vecSt[1], 1.0);
    EXPECT_FLOAT_EQ(vecSt[2], 1.0);
    EXPECT_FLOAT_EQ(vecSt[3], 1.0);
    
    Vec<double, 2> vecI3(1.0, 2.0);
    vecI3 /= 2.0;
    EXPECT_FLOAT_EQ(vecI3[0], 0.5);
    EXPECT_FLOAT_EQ(vecI3[1], 1.0);
    
    // Narrower number
    Vec<double, 2> vecI4(1.0, 2.0);
    vecI4 /= 2;
    EXPECT_FLOAT_EQ(vecI4[0], 0.5);
    EXPECT_FLOAT_EQ(vecI4[1], 1.0);
}


TEST(VectorTests, AdditionOperator) {
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    Vec<Vec<int, 2>, 2> vec2X22(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    Vec<Vec<int, 2>, 2> result2x2 = vec2X2 + vec2X22;
    EXPECT_EQ(result2x2[0][0], 2);
    EXPECT_EQ(result2x2[0][1], 4);
    EXPECT_EQ(result2x2[1][0], 6);
    EXPECT_EQ(result2x2[1][1], 8);
    
    Vec<int, 2> vecI(1, 2);
    Vec<int, 2> vecI2(1, 2);
    Vec<int, 2> result = vecI + vecI2;
    EXPECT_EQ(result[0], 2);
    EXPECT_EQ(result[1], 4);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    Vec<float, 3> vecF2(1.0, 2.0, 3.0);
    Vec<float, 3> resultF = vecF + vecF2;
    EXPECT_FLOAT_EQ(resultF[0], 2);
    EXPECT_FLOAT_EQ(resultF[1], 4);
    EXPECT_FLOAT_EQ(resultF[2], 6);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    Vec<size_t, 4> vecSt2(1, 2, 3, 4);
    Vec<size_t, 4> resultSt = vecSt + vecSt2;
    EXPECT_EQ(resultSt[0], 2);
    EXPECT_EQ(resultSt[1], 4);
    EXPECT_EQ(resultSt[2], 6);
    EXPECT_EQ(resultSt[3], 8);
    
    // A harder one
    Vec<size_t, 4> vecSt3(333, 222, 111, 444);
    Vec<size_t, 4> vecSt4(444, 111, 222, 333);
    Vec<size_t, 4> resultSt2 = vecSt3 + vecSt4;
    EXPECT_EQ(resultSt2[0], 777);
    EXPECT_EQ(resultSt2[1], 333);
    EXPECT_EQ(resultSt2[2], 333);
    EXPECT_EQ(resultSt2[3], 777);
}

TEST(VectorTests, SubtractionOperator) {
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    Vec<Vec<int, 2>, 2> vec2X22(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    Vec<Vec<int, 2>, 2> result2x2 = vec2X2 - vec2X22;
    EXPECT_EQ(result2x2[0][0], 0);
    EXPECT_EQ(result2x2[0][1], 0);
    EXPECT_EQ(result2x2[1][0], 0);
    EXPECT_EQ(result2x2[1][1], 0);
    
    Vec<int, 2> vecI(1, 2);
    Vec<int, 2> vecI2(1, 2);
    Vec<int, 2> result = vecI - vecI2;
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 0);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    Vec<float, 3> vecF2(1.0, 2.0, 3.0);
    Vec<float, 3> resultF = vecF - vecF2;
    EXPECT_FLOAT_EQ(resultF[0], 0);
    EXPECT_FLOAT_EQ(resultF[1], 0);
    EXPECT_FLOAT_EQ(resultF[2], 0);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    Vec<size_t, 4> vecSt2(1, 2, 3, 4);
    Vec<size_t, 4> resultSt = vecSt - vecSt2;
    EXPECT_EQ(resultSt[0], 0);
    EXPECT_EQ(resultSt[1], 0);
    EXPECT_EQ(resultSt[2], 0);
    EXPECT_EQ(resultSt[3], 0);
    
    // A harder one
    Vec<size_t, 4> vecSt3(333, 222, 111, 444);
    Vec<size_t, 4> vecSt4(444, 111, 222, 333);
    Vec<size_t, 4> resultSt2 = vecSt3 - vecSt4;
    EXPECT_EQ(resultSt2[0], -111);
    EXPECT_EQ(resultSt2[1], 111);
    EXPECT_EQ(resultSt2[2], -111);
    EXPECT_EQ(resultSt2[3], 111);
}


TEST(VectorTests, MultiplicationOperator) {
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    Vec<Vec<int, 2>, 2> vec2X22(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    Vec<Vec<int, 2>, 2> result2x2 = vec2X2 * vec2X22;
    EXPECT_EQ(result2x2[0][0], 1);
    EXPECT_EQ(result2x2[0][1], 4);
    EXPECT_EQ(result2x2[1][0], 9);
    EXPECT_EQ(result2x2[1][1], 16);
    
    Vec<int, 2> vecI(1, 2);
    Vec<int, 2> vecI2(1, 2);
    Vec<int, 2> result = vecI * vecI2;
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 4);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    Vec<float, 3> vecF2(1.0, 2.0, 3.0);
    Vec<float, 3> resultF = vecF * vecF2;
    EXPECT_FLOAT_EQ(resultF[0], 1);
    EXPECT_FLOAT_EQ(resultF[1], 4);
    EXPECT_FLOAT_EQ(resultF[2], 9);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    Vec<size_t, 4> vecSt2(1, 2, 3, 4);
    Vec<size_t, 4> resultSt = vecSt * vecSt2;
    EXPECT_EQ(resultSt[0], 1);
    EXPECT_EQ(resultSt[1], 4);
    EXPECT_EQ(resultSt[2], 9);
    EXPECT_EQ(resultSt[3], 16);
    
    // A harder one
    Vec<size_t, 4> vecSt3(333, 222, 111, 444);
    Vec<size_t, 4> vecSt4(3, 2, 3, 4);
    Vec<size_t, 4> resultSt2 = vecSt3 * vecSt4;
    EXPECT_EQ(resultSt2[0], 999);
    EXPECT_EQ(resultSt2[1], 444);
    EXPECT_EQ(resultSt2[2], 333);
    EXPECT_EQ(resultSt2[3], 1776);
}

TEST(VectorTests, DivisionOperator) {
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    Vec<Vec<int, 2>, 2> vec2X22(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    Vec<Vec<int, 2>, 2> result2x2 = vec2X2 / vec2X22;
    EXPECT_EQ(result2x2[0][0], 1);
    EXPECT_EQ(result2x2[0][1], 1);
    EXPECT_EQ(result2x2[1][0], 1);
    EXPECT_EQ(result2x2[1][1], 1);
    
    Vec<int, 2> vecI(1, 2);
    Vec<int, 2> vecI2(1, 2);
    Vec<int, 2> result = vecI / vecI2;
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 1);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    Vec<float, 3> vecF2(1.0, 2.0, 3.0);
    Vec<float, 3> resultF = vecF / vecF2;
    EXPECT_FLOAT_EQ(resultF[0], 1);
    EXPECT_FLOAT_EQ(resultF[1], 1);
    EXPECT_FLOAT_EQ(resultF[2], 1);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    Vec<size_t, 4> vecSt2(1, 2, 3, 4);
    Vec<size_t, 4> resultSt = vecSt / vecSt2;
    EXPECT_EQ(resultSt[0], 1);
    EXPECT_EQ(resultSt[1], 1);
    EXPECT_EQ(resultSt[2], 1);
    EXPECT_EQ(resultSt[3], 1);
    
    // A harder one
    Vec<size_t, 4> vecSt3(333, 222, 111, 444);
    Vec<size_t, 4> vecSt4(3, 2, 3, 4);
    Vec<size_t, 4> resultSt2 = vecSt3 / vecSt4;
    EXPECT_EQ(resultSt2[0], 111);
    EXPECT_EQ(resultSt2[1], 111);
    EXPECT_EQ(resultSt2[2], 37);
    EXPECT_EQ(resultSt2[3], 111);
    
    // A harder one
    Vec<double, 2> vecD(333.11, 222.32);
    Vec<double, 2> vecD2(3.32, 2.12);
    Vec<double, 2> resultD = vecD / vecD2;
    EXPECT_FLOAT_EQ(resultD[0], 100.334337);
    EXPECT_FLOAT_EQ(resultD[1], 104.867925);
}

// ---------------------------------------------------------------- //
// ------------------ Comparison Operators Tests ------------------ //
// ---------------------------------------------------------------- //

TEST(VectorTests, EqualityOperator) {
    Vec<int, 2> vecI(1, 2);
    Vec<int, 2> vecI2(1, 2);
    EXPECT_TRUE(vecI == vecI2);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    Vec<float, 3> vecF2(1.0, 2.0, 3.0);
    EXPECT_TRUE(vecF == vecF2);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    Vec<size_t, 4> vecSt2(1, 2, 3, 4);
    EXPECT_TRUE(vecSt == vecSt2);
    
    // A harder one
    Vec<size_t, 4> vecSt3(333, 222, 111, 444);
    Vec<size_t, 4> vecSt4(333, 222, 111, 444);
    EXPECT_TRUE(vecSt3 == vecSt4);
}

TEST(VectorTests, InequalityOperator) {
    Vec<int, 2> vecI(1, 2);
    Vec<int, 2> vecI2(1, 2);
    EXPECT_FALSE(vecI != vecI2);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    Vec<float, 3> vecF2(1.0, 2.0, 3.0);
    EXPECT_FALSE(vecF != vecF2);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    Vec<size_t, 4> vecSt2(1, 2, 3, 4);
    EXPECT_FALSE(vecSt != vecSt2);
    
    // A harder one
    Vec<size_t, 4> vecSt3(333, 222, 111, 444);
    Vec<size_t, 4> vecSt4(333, 222, 111, 444);
    EXPECT_FALSE(vecSt3 != vecSt4);
}

TEST(VectorTests, LessThanOperator) {
    Vec<int, 2> vecI(1, 2);
    Vec<int, 2> vecI2(1, 2);
    EXPECT_FALSE(vecI < vecI2);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    Vec<float, 3> vecF2(1.0, 2.0, 3.0);
    EXPECT_FALSE(vecF < vecF2);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    Vec<size_t, 4> vecSt2(1, 2, 3, 4);
    EXPECT_FALSE(vecSt < vecSt2);
    
    // A harder one
    Vec<size_t, 4> vecSt3(333, 222, 111, 444);
    Vec<size_t, 4> vecSt4(333, 222, 111, 444);
    EXPECT_FALSE(vecSt3 < vecSt4);
    
    // A harder one
    Vec<size_t, 4> vecSt5(333, 222, 111, 444);
    Vec<size_t, 4> vecSt6(333, 222, 111, 445);
    EXPECT_TRUE(vecSt5 < vecSt6);
}

TEST(VectorTests, LessThanOrEqualOperator) {
    Vec<int, 2> vecI(1, 2);
    Vec<int, 2> vecI2(1, 2);
    EXPECT_TRUE(vecI <= vecI2);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    Vec<float, 3> vecF2(1.0, 2.0, 3.0);
    EXPECT_TRUE(vecF <= vecF2);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    Vec<size_t, 4> vecSt2(1, 2, 3, 4);
    EXPECT_TRUE(vecSt <= vecSt2);
    
    // A harder one
    Vec<size_t, 4> vecSt3(333, 222, 111, 444);
    Vec<size_t, 4> vecSt4(333, 222, 111, 444);
    EXPECT_TRUE(vecSt3 <= vecSt4);
    
    // A harder one
    Vec<size_t, 4> vecSt5(333, 222, 111, 444);
    Vec<size_t, 4> vecSt6(333, 222, 111, 445);
    EXPECT_TRUE(vecSt5 <= vecSt6);
}

TEST(VectorTests, GreaterThanOperator) {
    Vec<int, 2> vecI(1, 2);
    Vec<int, 2> vecI2(1, 2);
    EXPECT_FALSE(vecI > vecI2);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    Vec<float, 3> vecF2(1.0, 2.0, 3.0);
    EXPECT_FALSE(vecF > vecF2);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    Vec<size_t, 4> vecSt2(1, 2, 3, 4);
    EXPECT_FALSE(vecSt > vecSt2);
    
    // A harder one
    Vec<size_t, 4> vecSt3(333, 222, 111, 444);
    Vec<size_t, 4> vecSt4(333, 222, 111, 444);
    EXPECT_FALSE(vecSt3 > vecSt4);
    
    // A harder one
    Vec<size_t, 4> vecSt5(333, 222, 111, 444);
    Vec<size_t, 4> vecSt6(333, 222, 111, 445);
    EXPECT_FALSE(vecSt5 > vecSt6);
    
    // A harder one
    Vec<size_t, 4> vecSt7(333, 222, 111, 444);
    Vec<size_t, 4> vecSt8(333, 222, 111, 443);
    EXPECT_TRUE(vecSt7 > vecSt8);
}

TEST(VectorTests, GreaterOrEqualThanOperator) {
    Vec<int, 2> vecI(1, 2);
    Vec<int, 2> vecI2(1, 2);
    EXPECT_TRUE(vecI >= vecI2);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    Vec<float, 3> vecF2(1.0, 2.0, 3.0);
    EXPECT_TRUE(vecF >= vecF2);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    Vec<size_t, 4> vecSt2(1, 2, 3, 4);
    EXPECT_TRUE(vecSt >= vecSt2);
    
    // A harder one
    Vec<size_t, 4> vecSt3(333, 222, 111, 444);
    Vec<size_t, 4> vecSt4(333, 222, 111, 444);
    EXPECT_TRUE(vecSt3 >= vecSt4);
    
    // A harder one
    Vec<size_t, 4> vecSt5(333, 222, 111, 444);
    Vec<size_t, 4> vecSt6(333, 222, 111, 445);
    EXPECT_FALSE(vecSt5 >= vecSt6);
    
    // A harder one
    Vec<size_t, 4> vecSt7(333, 222, 111, 444);
    Vec<size_t, 4> vecSt8(333, 222, 111, 443);
    EXPECT_TRUE(vecSt7 >= vecSt8);
}

// ---------------------------------------------------------------- //
// --------------------- Vector Functions ------------------------- //
// ---------------------------------------------------------------- //

TEST(VectorTests, DotProduct) {
    Vec<int, 2> vecI(1, 2);
    Vec<int, 2> vecI2(1, 2);
    EXPECT_EQ(vecI.dot(vecI2), 5);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    Vec<float, 3> vecF2(1.0, 2.0, 3.0);
    EXPECT_FLOAT_EQ(vecF.dot(vecF2), 14.0);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    Vec<size_t, 4> vecSt2(1, 2, 3, 4);
    EXPECT_EQ(vecSt.dot(vecSt2), 30);
    
    Vec<float, 4> vecSt3(1.11f, 2.22f, 1.11f, 4.44f);
    Vec<float, 4> vecSt4(3.33f, 2.22f, 1.11f, 4.44f);
    EXPECT_FLOAT_EQ(vecSt3.dot(vecSt4), 29.5704f);
    
    Vec<size_t, 3> vecSt5(333, 222, 111);
    Vec<size_t, 3> vecSt6(333, 222, 111);
    EXPECT_EQ(vecSt5.dot(vecSt6), 172494);
}

TEST(VectorTests, Length) {
    Vec<int, 2> vecI(1, 2);
    EXPECT_EQ(vecI.length(), 2);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    EXPECT_FLOAT_EQ(vecF.length(), 3.7416573868);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    EXPECT_EQ(vecSt.length(), 5);
    
    // A harder one
    Vec<float, 4> vecSt3(1.11f, 2.22f, 1.11f, 4.44f);
    EXPECT_FLOAT_EQ(vecSt3.length(), 5.206361493404008f);
}

// lenght squared
TEST(VectorTests, LengthSquared) {
    Vec<int, 2> vecI(1, 2);
    EXPECT_EQ(vecI.lengthSquared(), 5);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    EXPECT_EQ(vecF.lengthSquared(), 14.0);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    EXPECT_EQ(vecSt.lengthSquared(), 30);
    
    // A harder one
    Vec<float, 4> vecSt3(1.11f, 2.22f, 1.11f, 4.44f);
    EXPECT_FLOAT_EQ(vecSt3.lengthSquared(), 27.106201f);
}

TEST(VectorTests, Normalize) {
    Vec<int, 2> vecI(1, 2);
    Vec<int, 2> normI = vecI.normalize();
    EXPECT_EQ(normI[0], 0);
    EXPECT_EQ(normI[1], 1);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    Vec<float, 3> normF = vecF.normalize();
    EXPECT_FLOAT_EQ(normF[0], 0.2672612419);
    EXPECT_FLOAT_EQ(normF[1], 0.5345224838);
    EXPECT_FLOAT_EQ(normF[2], 0.8017837257);
    
    Vec<size_t, 4> vecSt(10, 66, 123, 21);
    Vec<size_t, 4> normSt = vecSt.normalize();
    EXPECT_EQ(normSt[0], 0); // All zeros because of integer division
    EXPECT_EQ(normSt[1], 0);
    EXPECT_EQ(normSt[2], 0);
    EXPECT_EQ(normSt[3], 0);
    
}

TEST(VectorTests, Cross) {
    // Test with unit vectors
    Vec<float, 3> i(1.0f, 0.0f, 0.0f);
    Vec<float, 3> j(0.0f, 1.0f, 0.0f);
    Vec<float, 3> k(0.0f, 0.0f, 1.0f);
    
    EXPECT_FLOAT_EQ((i.cross(j))[2], 1.0f);
    EXPECT_FLOAT_EQ((j.cross(k))[0], 1.0f);
    EXPECT_FLOAT_EQ((k.cross(i))[1], 1.0f);
    
    // Test with zero vectors
    Vec<float, 3> zero(0.0f, 0.0f, 0.0f);
    Vec<float, 3> result = i.cross(zero);
    EXPECT_FLOAT_EQ(result[0], 0.0f);
    EXPECT_FLOAT_EQ(result[1], 0.0f);
    EXPECT_FLOAT_EQ(result[2], 0.0f);
    
    // Test with parallel vectors (should result in a zero vector)
    Vec<float, 3> parallel = i * 2.0f;
    result = i.cross(parallel);
    EXPECT_FLOAT_EQ(result[0], 0.0f);
    EXPECT_FLOAT_EQ(result[1], 0.0f);
    EXPECT_FLOAT_EQ(result[2], 0.0f);
    
    // Test with opposite vectors (should also result in a zero vector)
    Vec<float, 3> opposite = i * -1.0f;
    result = i.cross(opposite);
    EXPECT_FLOAT_EQ(result[0], 0.0f);
    EXPECT_FLOAT_EQ(result[1], 0.0f);
    EXPECT_FLOAT_EQ(result[2], 0.0f);
    
    // Test with arbitrary vectors
    Vec<float, 3> vec1(3.0f, -3.0f, 1.0f);
    Vec<float, 3> vec2(4.0f, 9.0f, 2.0f);
    result = vec1.cross(vec2);
    EXPECT_FLOAT_EQ(result[0], -15.0f);
    EXPECT_FLOAT_EQ(result[1], -2.0f);
    EXPECT_FLOAT_EQ(result[2], 39.0f);
}

TEST(VectorTests, toString) {
    Vec<int, 2> vecI(1, 2);
    EXPECT_EQ(vecI.toString(), "[1, 2]");
    
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    EXPECT_EQ(vecF.toString(), std::string(
            "[" + std::to_string(vecF[0]) +
            ", " + std::to_string(vecF[1]) +
            ", " + std::to_string(vecF[2]) + "]"));
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    EXPECT_EQ(vecSt.toString(), std::string(
            "[" + std::to_string(vecSt[0]) +
            ", " + std::to_string(vecSt[1]) +
            ", " + std::to_string(vecSt[2]) +
            ", " + std::to_string(vecSt[3]) + "]"));
    
    // A harder one
    Vec<float, 4> vecSt3(1.11f, 2.22f, 1.11f, 4.44f);
    EXPECT_EQ(vecSt3.toString(), std::string(
            "[" + std::to_string(vecSt3[0]) +
            ", " + std::to_string(vecSt3[1]) +
            ", " + std::to_string(vecSt3[2]) +
            ", " + std::to_string(vecSt3[3]) + "]"));
}
