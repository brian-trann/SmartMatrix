/*
 * SmartMatrix Library - APA102 Panel Calculation Class
 *
 * Copyright (c) 2017 Louis Beaudoin (Pixelmatix)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef SmartMatrixAPA102Calc_h
#define SmartMatrixAPA102Calc_h

#define SMARTMATRIX_APA102_OPTIONS_NONE                 0
#define SMARTMATRIX_APA102_OPTIONS_GBC_MODE_DEFAULT     (0x0 << 0)
#define SMARTMATRIX_APA102_OPTIONS_GBC_MODE_SIMPLE      (0x1 << 0)
#define SMARTMATRIX_APA102_OPTIONS_GBC_MODE_NONE        (0x2 << 0)
#define SMARTMATRIX_APA102_OPTIONS_GBC_MODE_BRIGHTONLY  (0x3 << 0)
#define SMARTMATRIX_APA102_OPTIONS_GBC_MODE_MASK        (0x3 << 0)

#define SMARTMATRIX_APA102_OPTIONS_COLOR_ORDER_BGR      (0x0 << 2)
#define SMARTMATRIX_APA102_OPTIONS_COLOR_ORDER_RBG      (0x1 << 2)
#define SMARTMATRIX_APA102_OPTIONS_COLOR_ORDER_GRB      (0x2 << 2)
#define SMARTMATRIX_APA102_OPTIONS_COLOR_ORDER_GBR      (0x3 << 2)
#define SMARTMATRIX_APA102_OPTIONS_COLOR_ORDER_RGB      (0x4 << 2)
#define SMARTMATRIX_APA102_OPTIONS_COLOR_ORDER_BRG      (0x5 << 2)
#define SMARTMATRIX_APA102_OPTIONS_COLOR_ORDER_MASK     (0x7 << 2)

template <int refreshDepth, int matrixWidth, int matrixHeight, unsigned char panelType, uint32_t optionFlags>
class SmartMatrixApaCalc {
public:
    typedef typename SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::frameDataStruct frameDataStruct;

    // init
    SmartMatrixApaCalc(uint8_t bufferrows, frameDataStruct * rowDataBuffer);
    void begin(void);
    void addLayer(SM_Layer * newlayer);

    // configuration
    void setRotation(rotationDegrees rotation);
    void setBrightness(uint8_t newBrightness);
    void setRefreshRate(uint8_t newRefreshRate);
    void setSpiClockSpeed(uint32_t newClockSpeed);

    // get info
    uint16_t getScreenWidth(void) const;
    uint16_t getScreenHeight(void) const;
    uint8_t getRefreshRate(void);
    bool getdmaBufferUnderrunFlag(void);
    bool getRefreshRateLoweredFlag(void);

    // debug
    int countFPS(void);

    // functions called by ISR
    static void matrixCalculations(bool initial);
    static void dmaBufferUnderrunCallback(void);

private:
    static SM_Layer * baseLayer;

    // functions for refreshing
    static void loadMatrixBuffers(frameDataStruct * currentRowDataPtr, unsigned char currentRow);

    // configuration
    static volatile bool rotationChange;
    static volatile bool dmaBufferUnderrun;
    static int dimmingFactor;
    static const int dimmingMaximum = 255;
    static rotationDegrees rotation;
    static uint8_t refreshRate;
    static uint32_t spiClockSpeed;
    static bool dmaBufferUnderrunSinceLastCheck;
    static bool refreshRateLowered;
    static bool refreshRateChanged;
};

#endif
