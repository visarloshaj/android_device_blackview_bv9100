#
# Copyright (C) 2019 The LineageOS Project
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

import common

def FullOTA_InstallEnd(info):
  input_zip = info.input_zip
  OTA_InstallEnd(info, input_zip)

def IncrementalOTA_InstallEnd(info):
  input_zip = info.target_zip
  OTA_InstallEnd(info, input_zip)

def AddImage(info, input_zip, basename, dest):
  path = "IMAGES/" + basename
  if path not in input_zip.namelist():
    return

  data = input_zip.read(path)
  common.ZipWriteStr(info.output_zip, basename, data)
  info.script.AppendExtra('package_extract_file("%s", "%s");' % (basename, dest))

def OTA_InstallEnd(info, input_zip):
  info.script.Print("Patching vbmeta image...")
  AddImage(info, input_zip, "vbmeta.img", "/dev/block/bootdevice/by-name/vbmeta")

  #info.script.Print("Flashing scp firmware...")
  #AddImage(info, input_zip, "scp.img", "/dev/block/bootdevice/by-name/scp1")
  #AddImage(info, input_zip, "scp.img", "/dev/block/bootdevice/by-name/scp2")
