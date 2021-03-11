#
# Copyright (C) 2021 The LineageOS Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/product_launched_with_p.mk)

# Inherit some common Lineage stuff
$(call inherit-product, vendor/revengeos/config/common.mk)

# Inherit from Blackview BV9100 device
$(call inherit-product, $(LOCAL_PATH)/device.mk)

# Boot Animation RES
TARGET_BOOT_ANIMATION_RES := 1080

# Device identifier. This must come after all inclusions.
PRODUCT_BRAND := Blackview
PRODUCT_DEVICE := bv9100
PRODUCT_MANUFACTURER := Blackview
PRODUCT_NAME := revengeos_bv9100
PRODUCT_MODEL := Blackview BV9100

# Override PRODUCT_DEVICE to keep TrustKernel happy.
PRODUCT_BUILD_PROP_OVERRIDES += \
    PRODUCT_DEVICE=BV9100

