#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <string>

using namespace std;
class Console
{
public:
    static void init();
    /**
     * @brief Display error messages
     * Background -- Red
     * Text       -- Black Bold
     *
     * @param text printed text
     */
    static void error(string text);
    /**
     * @brief Display warning messages
     * Background -- Black
     * Text       -- Yellow
     *
     * @param text printed text
     */
    static void warning(string text);
    /**
     * @brief Display basic information
     * Background -- Black
     * Text       -- Gray
     *
     * @param text printed text
     */
    static void info(string text);
    /**
     * @brief Display important information
     * Background -- Black
     * Text       -- Gray Bold
     *
     * @param text printed text
     */
    static void importantInfo(string text);
    /**
     * @brief Display important information
     * Background -- Green
     * Text       -- White Bold
     *
     * @param text printed text
     */
    static void success(string text);

};