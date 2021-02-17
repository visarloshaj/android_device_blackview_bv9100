/*
 * Copyright (C) 2019 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "TouchscreenGestureService"

#include "TouchscreenGesture.h"
#include <android-base/logging.h>
#include <fstream>

namespace vendor {
namespace lineage {
namespace touch {
namespace V1_0 {
namespace implementation {

const std::map<int32_t, TouchscreenGesture::GestureInfo> TouchscreenGesture::kGestureInfoMap = {
    {0, {103, "One finger up swipe", "/sys/devices/platform/11007000.i2c0/i2c-0/0-005d/swipe_up_switch"}},
    {1, {106, "One finger right swipe", "/sys/devices/platform/11007000.i2c0/i2c-0/0-005d/swipe_right_switch"}},
    {2, {108, "One finger down swipe", "/sys/devices/platform/11007000.i2c0/i2c-0/0-005d/swipe_down_switch"}},
    {3, {105, "One finger left swipe", "/sys/devices/platform/11007000.i2c0/i2c-0/0-005d/swipe_left_switch"}},
    {4, {50, "Letter M", "/sys/devices/platform/11007000.i2c0/i2c-0/0-005d/letter_m_switch"}},
    {5, {24, "Letter O", "/sys/devices/platform/11007000.i2c0/i2c-0/0-005d/letter_o_switch"}},
    {6, {31, "Letter S", "/sys/devices/platform/11007000.i2c0/i2c-0/0-005d/letter_s_switch"}},
    {7, {17, "Letter W", "/sys/devices/platform/11007000.i2c0/i2c-0/0-005d/letter_w_switch"}},
    {8, {46, "Letter C", "/sys/devices/platform/11007000.i2c0/i2c-0/0-005d/letter_c_switch"}},
    {9, {38, "Letter L", "/sys/devices/platform/11007000.i2c0/i2c-0/0-005d/letter_l_switch"}},
    {10, {47, "Letter V", "/sys/devices/platform/11007000.i2c0/i2c-0/0-005d/letter_v_switch"}},
    {11, {44, "Letter Z", "/sys/devices/platform/11007000.i2c0/i2c-0/0-005d/letter_z_switch"}},
    {12, {18, "Letter e", "/sys/devices/platform/11007000.i2c0/i2c-0/0-005d/letter_e_switch"}},
};

Return<void> TouchscreenGesture::getSupportedGestures(getSupportedGestures_cb resultCb) {
    std::vector<Gesture> gestures;

    for (const auto& entry : kGestureInfoMap) {
        if (access(entry.second.path, F_OK) != -1) {
            gestures.push_back({entry.first, entry.second.name, entry.second.keycode});
        }
    }
    resultCb(gestures);

    return Void();
}

Return<bool> TouchscreenGesture::setGestureEnabled(
    const ::vendor::lineage::touch::V1_0::Gesture& gesture, bool enabled) {
    const auto entry = kGestureInfoMap.find(gesture.id);
    if (entry == kGestureInfoMap.end()) {
        return false;
    }

    std::ofstream file(entry->second.path);
    file << (enabled ? "1" : "0");
    LOG(DEBUG) << "Wrote file " << entry->second.path << " fail " << file.fail();
    return !file.fail();
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace touch
}  // namespace lineage
}  // namespace vendor
