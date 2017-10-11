/*
 * Copyright (C) 2017 The Android Open Source Project
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

#ifndef ART_RUNTIME_NATIVE_DEX_FILE_H_
#define ART_RUNTIME_NATIVE_DEX_FILE_H_

#include <iosfwd>

#include "dex_file.h"

namespace art {

class OatDexFile;

// Native (ordinary) dex file. This is the format that is packaged in APKs and produced by tools.
class NativeDexFile : public DexFile {
 public:
  static const uint8_t kDexMagic[kDexMagicSize];
  static constexpr size_t kNumDexVersions = 4;
  static const uint8_t kDexMagicVersions[kNumDexVersions][kDexVersionLen];

  // Returns true if the byte string points to the magic value.
  static bool IsMagicValid(const uint8_t* magic);
  virtual bool IsMagicValid() const OVERRIDE;

  // Returns true if the byte string after the magic is the correct value.
  static bool IsVersionValid(const uint8_t* magic);
  virtual bool IsVersionValid() const OVERRIDE;

 private:
  NativeDexFile(const uint8_t* base,
                size_t size,
                const std::string& location,
                uint32_t location_checksum,
                const OatDexFile* oat_dex_file)
      : DexFile(base, size, location, location_checksum, oat_dex_file) {}

  friend class DexFile;
  friend class DexFileVerifierTest;

  ART_FRIEND_TEST(ClassLinkerTest, RegisterDexFileName);  // for constructor

  DISALLOW_COPY_AND_ASSIGN(NativeDexFile);
};

}  // namespace art

#endif  // ART_RUNTIME_NATIVE_DEX_FILE_H_
