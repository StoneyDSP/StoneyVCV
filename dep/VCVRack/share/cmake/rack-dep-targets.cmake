# Generated by CMake

if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.8)
   message(FATAL_ERROR "CMake >= 3.0.0 required")
endif()
if(CMAKE_VERSION VERSION_LESS "3.0.0")
   message(FATAL_ERROR "CMake >= 3.0.0 required")
endif()
cmake_policy(PUSH)
cmake_policy(VERSION 3.0.0...3.29)
#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Protect against multiple inclusion, which would fail when already imported targets are added once more.
set(_cmake_targets_defined "")
set(_cmake_targets_not_defined "")
set(_cmake_expected_targets "")
foreach(_cmake_expected_target IN ITEMS rack::dep)
  list(APPEND _cmake_expected_targets "${_cmake_expected_target}")
  if(TARGET "${_cmake_expected_target}")
    list(APPEND _cmake_targets_defined "${_cmake_expected_target}")
  else()
    list(APPEND _cmake_targets_not_defined "${_cmake_expected_target}")
  endif()
endforeach()
unset(_cmake_expected_target)
if(_cmake_targets_defined STREQUAL _cmake_expected_targets)
  unset(_cmake_targets_defined)
  unset(_cmake_targets_not_defined)
  unset(_cmake_expected_targets)
  unset(CMAKE_IMPORT_FILE_VERSION)
  cmake_policy(POP)
  return()
endif()
if(NOT _cmake_targets_defined STREQUAL "")
  string(REPLACE ";" ", " _cmake_targets_defined_text "${_cmake_targets_defined}")
  string(REPLACE ";" ", " _cmake_targets_not_defined_text "${_cmake_targets_not_defined}")
  message(FATAL_ERROR "Some (but not all) targets in this export set were already defined.\nTargets Defined: ${_cmake_targets_defined_text}\nTargets not yet defined: ${_cmake_targets_not_defined_text}\n")
endif()
unset(_cmake_targets_defined)
unset(_cmake_targets_not_defined)
unset(_cmake_expected_targets)


# Compute the installation prefix relative to this file.
get_filename_component(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
if(_IMPORT_PREFIX STREQUAL "/")
  set(_IMPORT_PREFIX "")
endif()

# Create imported target rack::dep
add_library(rack::dep INTERFACE IMPORTED)

set_target_properties(rack::dep PROPERTIES
  COMPATIBLE_INTERFACE_STRING "INTERFACE_dep_MAJOR_VERSION;INTERFACE_dep_MINOR_VERSION;INTERFACE_dep_PATCH_VERSION"
  INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include"
)

if(NOT CMAKE_VERSION VERSION_LESS "3.23.0")
  target_sources(rack::dep
    INTERFACE
      FILE_SET "rack_DEP_INTERFACE_HEADERS"
      TYPE "HEADERS"
      BASE_DIRS "${_IMPORT_PREFIX}/include/dep"
      FILES "${_IMPORT_PREFIX}/include/dep/FuzzySearchDatabase.hpp" "${_IMPORT_PREFIX}/include/dep/archive.h" "${_IMPORT_PREFIX}/include/dep/archive_entry.h" "${_IMPORT_PREFIX}/include/dep/blendish.h" "${_IMPORT_PREFIX}/include/dep/cover.h" "${_IMPORT_PREFIX}/include/dep/fftpack.h" "${_IMPORT_PREFIX}/include/dep/fontstash.h" "${_IMPORT_PREFIX}/include/dep/jansson.h" "${_IMPORT_PREFIX}/include/dep/jansson_config.h" "${_IMPORT_PREFIX}/include/dep/nanosvg.h" "${_IMPORT_PREFIX}/include/dep/nanosvgrast.h" "${_IMPORT_PREFIX}/include/dep/nanovg.h" "${_IMPORT_PREFIX}/include/dep/nanovg_gl.h" "${_IMPORT_PREFIX}/include/dep/nanovg_gl_utils.h" "${_IMPORT_PREFIX}/include/dep/osdialog.h" "${_IMPORT_PREFIX}/include/dep/oui.h" "${_IMPORT_PREFIX}/include/dep/pffft.h" "${_IMPORT_PREFIX}/include/dep/samplerate.h" "${_IMPORT_PREFIX}/include/dep/stb_image.h" "${_IMPORT_PREFIX}/include/dep/stb_image_write.h" "${_IMPORT_PREFIX}/include/dep/stb_truetype.h" "${_IMPORT_PREFIX}/include/dep/tinyexpr.h" "${_IMPORT_PREFIX}/include/dep/zbuff.h" "${_IMPORT_PREFIX}/include/dep/zdict.h" "${_IMPORT_PREFIX}/include/dep/zstd.h" "${_IMPORT_PREFIX}/include/dep/zstd_errors.h" "${_IMPORT_PREFIX}/include/dep/GL/glew.h" "${_IMPORT_PREFIX}/include/dep/GL/glxew.h" "${_IMPORT_PREFIX}/include/dep/GL/wglew.h" "${_IMPORT_PREFIX}/include/dep/GLFW/glfw3.h" "${_IMPORT_PREFIX}/include/dep/GLFW/glfw3native.h" "${_IMPORT_PREFIX}/include/dep/curl/curl.h" "${_IMPORT_PREFIX}/include/dep/curl/curlver.h" "${_IMPORT_PREFIX}/include/dep/curl/easy.h" "${_IMPORT_PREFIX}/include/dep/curl/mprintf.h" "${_IMPORT_PREFIX}/include/dep/curl/multi.h" "${_IMPORT_PREFIX}/include/dep/curl/options.h" "${_IMPORT_PREFIX}/include/dep/curl/stdcheaders.h" "${_IMPORT_PREFIX}/include/dep/curl/system.h" "${_IMPORT_PREFIX}/include/dep/curl/typecheck-gcc.h" "${_IMPORT_PREFIX}/include/dep/curl/urlapi.h" "${_IMPORT_PREFIX}/include/dep/ghc/filesystem.hpp" "${_IMPORT_PREFIX}/include/dep/ghc/fs_fwd.hpp" "${_IMPORT_PREFIX}/include/dep/ghc/fs_impl.hpp" "${_IMPORT_PREFIX}/include/dep/ghc/fs_std.hpp" "${_IMPORT_PREFIX}/include/dep/ghc/fs_std_fwd.hpp" "${_IMPORT_PREFIX}/include/dep/ghc/fs_std_impl.hpp" "${_IMPORT_PREFIX}/include/dep/openssl/aes.h" "${_IMPORT_PREFIX}/include/dep/openssl/asn1.h" "${_IMPORT_PREFIX}/include/dep/openssl/asn1_mac.h" "${_IMPORT_PREFIX}/include/dep/openssl/asn1err.h" "${_IMPORT_PREFIX}/include/dep/openssl/asn1t.h" "${_IMPORT_PREFIX}/include/dep/openssl/async.h" "${_IMPORT_PREFIX}/include/dep/openssl/asyncerr.h" "${_IMPORT_PREFIX}/include/dep/openssl/bio.h" "${_IMPORT_PREFIX}/include/dep/openssl/bioerr.h" "${_IMPORT_PREFIX}/include/dep/openssl/blowfish.h" "${_IMPORT_PREFIX}/include/dep/openssl/bn.h" "${_IMPORT_PREFIX}/include/dep/openssl/bnerr.h" "${_IMPORT_PREFIX}/include/dep/openssl/buffer.h" "${_IMPORT_PREFIX}/include/dep/openssl/buffererr.h" "${_IMPORT_PREFIX}/include/dep/openssl/camellia.h" "${_IMPORT_PREFIX}/include/dep/openssl/cast.h" "${_IMPORT_PREFIX}/include/dep/openssl/cmac.h" "${_IMPORT_PREFIX}/include/dep/openssl/cms.h" "${_IMPORT_PREFIX}/include/dep/openssl/cmserr.h" "${_IMPORT_PREFIX}/include/dep/openssl/comp.h" "${_IMPORT_PREFIX}/include/dep/openssl/comperr.h" "${_IMPORT_PREFIX}/include/dep/openssl/conf.h" "${_IMPORT_PREFIX}/include/dep/openssl/conf_api.h" "${_IMPORT_PREFIX}/include/dep/openssl/conferr.h" "${_IMPORT_PREFIX}/include/dep/openssl/crypto.h" "${_IMPORT_PREFIX}/include/dep/openssl/cryptoerr.h" "${_IMPORT_PREFIX}/include/dep/openssl/ct.h" "${_IMPORT_PREFIX}/include/dep/openssl/cterr.h" "${_IMPORT_PREFIX}/include/dep/openssl/des.h" "${_IMPORT_PREFIX}/include/dep/openssl/dh.h" "${_IMPORT_PREFIX}/include/dep/openssl/dherr.h" "${_IMPORT_PREFIX}/include/dep/openssl/dsa.h" "${_IMPORT_PREFIX}/include/dep/openssl/dsaerr.h" "${_IMPORT_PREFIX}/include/dep/openssl/dtls1.h" "${_IMPORT_PREFIX}/include/dep/openssl/e_os2.h" "${_IMPORT_PREFIX}/include/dep/openssl/ebcdic.h" "${_IMPORT_PREFIX}/include/dep/openssl/ec.h" "${_IMPORT_PREFIX}/include/dep/openssl/ecdh.h" "${_IMPORT_PREFIX}/include/dep/openssl/ecdsa.h" "${_IMPORT_PREFIX}/include/dep/openssl/ecerr.h" "${_IMPORT_PREFIX}/include/dep/openssl/engine.h" "${_IMPORT_PREFIX}/include/dep/openssl/engineerr.h" "${_IMPORT_PREFIX}/include/dep/openssl/err.h" "${_IMPORT_PREFIX}/include/dep/openssl/evp.h" "${_IMPORT_PREFIX}/include/dep/openssl/evperr.h" "${_IMPORT_PREFIX}/include/dep/openssl/hmac.h" "${_IMPORT_PREFIX}/include/dep/openssl/idea.h" "${_IMPORT_PREFIX}/include/dep/openssl/kdf.h" "${_IMPORT_PREFIX}/include/dep/openssl/kdferr.h" "${_IMPORT_PREFIX}/include/dep/openssl/lhash.h" "${_IMPORT_PREFIX}/include/dep/openssl/md2.h" "${_IMPORT_PREFIX}/include/dep/openssl/md4.h" "${_IMPORT_PREFIX}/include/dep/openssl/md5.h" "${_IMPORT_PREFIX}/include/dep/openssl/mdc2.h" "${_IMPORT_PREFIX}/include/dep/openssl/modes.h" "${_IMPORT_PREFIX}/include/dep/openssl/obj_mac.h" "${_IMPORT_PREFIX}/include/dep/openssl/objects.h" "${_IMPORT_PREFIX}/include/dep/openssl/objectserr.h" "${_IMPORT_PREFIX}/include/dep/openssl/ocsp.h" "${_IMPORT_PREFIX}/include/dep/openssl/ocsperr.h" "${_IMPORT_PREFIX}/include/dep/openssl/opensslconf.h" "${_IMPORT_PREFIX}/include/dep/openssl/opensslv.h" "${_IMPORT_PREFIX}/include/dep/openssl/ossl_typ.h" "${_IMPORT_PREFIX}/include/dep/openssl/pem.h" "${_IMPORT_PREFIX}/include/dep/openssl/pem2.h" "${_IMPORT_PREFIX}/include/dep/openssl/pemerr.h" "${_IMPORT_PREFIX}/include/dep/openssl/pkcs12.h" "${_IMPORT_PREFIX}/include/dep/openssl/pkcs12err.h" "${_IMPORT_PREFIX}/include/dep/openssl/pkcs7.h" "${_IMPORT_PREFIX}/include/dep/openssl/pkcs7err.h" "${_IMPORT_PREFIX}/include/dep/openssl/rand.h" "${_IMPORT_PREFIX}/include/dep/openssl/rand_drbg.h" "${_IMPORT_PREFIX}/include/dep/openssl/randerr.h" "${_IMPORT_PREFIX}/include/dep/openssl/rc2.h" "${_IMPORT_PREFIX}/include/dep/openssl/rc4.h" "${_IMPORT_PREFIX}/include/dep/openssl/rc5.h" "${_IMPORT_PREFIX}/include/dep/openssl/ripemd.h" "${_IMPORT_PREFIX}/include/dep/openssl/rsa.h" "${_IMPORT_PREFIX}/include/dep/openssl/rsaerr.h" "${_IMPORT_PREFIX}/include/dep/openssl/safestack.h" "${_IMPORT_PREFIX}/include/dep/openssl/seed.h" "${_IMPORT_PREFIX}/include/dep/openssl/sha.h" "${_IMPORT_PREFIX}/include/dep/openssl/srp.h" "${_IMPORT_PREFIX}/include/dep/openssl/srtp.h" "${_IMPORT_PREFIX}/include/dep/openssl/ssl.h" "${_IMPORT_PREFIX}/include/dep/openssl/ssl2.h" "${_IMPORT_PREFIX}/include/dep/openssl/ssl3.h" "${_IMPORT_PREFIX}/include/dep/openssl/sslerr.h" "${_IMPORT_PREFIX}/include/dep/openssl/stack.h" "${_IMPORT_PREFIX}/include/dep/openssl/store.h" "${_IMPORT_PREFIX}/include/dep/openssl/storeerr.h" "${_IMPORT_PREFIX}/include/dep/openssl/symhacks.h" "${_IMPORT_PREFIX}/include/dep/openssl/tls1.h" "${_IMPORT_PREFIX}/include/dep/openssl/ts.h" "${_IMPORT_PREFIX}/include/dep/openssl/tserr.h" "${_IMPORT_PREFIX}/include/dep/openssl/txt_db.h" "${_IMPORT_PREFIX}/include/dep/openssl/ui.h" "${_IMPORT_PREFIX}/include/dep/openssl/uierr.h" "${_IMPORT_PREFIX}/include/dep/openssl/whrlpool.h" "${_IMPORT_PREFIX}/include/dep/openssl/x509.h" "${_IMPORT_PREFIX}/include/dep/openssl/x509_vfy.h" "${_IMPORT_PREFIX}/include/dep/openssl/x509err.h" "${_IMPORT_PREFIX}/include/dep/openssl/x509v3.h" "${_IMPORT_PREFIX}/include/dep/openssl/x509v3err.h" "${_IMPORT_PREFIX}/include/dep/rtaudio/RtAudio.h" "${_IMPORT_PREFIX}/include/dep/rtaudio/rtaudio_c.h" "${_IMPORT_PREFIX}/include/dep/rtmidi/RtMidi.h" "${_IMPORT_PREFIX}/include/dep/rtmidi/rtmidi_c.h" "${_IMPORT_PREFIX}/include/dep/simde/check.h" "${_IMPORT_PREFIX}/include/dep/simde/debug-trap.h" "${_IMPORT_PREFIX}/include/dep/simde/hedley.h" "${_IMPORT_PREFIX}/include/dep/simde/simde-align.h" "${_IMPORT_PREFIX}/include/dep/simde/simde-arch.h" "${_IMPORT_PREFIX}/include/dep/simde/simde-common.h" "${_IMPORT_PREFIX}/include/dep/simde/simde-complex.h" "${_IMPORT_PREFIX}/include/dep/simde/simde-constify.h" "${_IMPORT_PREFIX}/include/dep/simde/simde-detect-clang.h" "${_IMPORT_PREFIX}/include/dep/simde/simde-diagnostic.h" "${_IMPORT_PREFIX}/include/dep/simde/simde-f16.h" "${_IMPORT_PREFIX}/include/dep/simde/simde-features.h" "${_IMPORT_PREFIX}/include/dep/simde/simde-math.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/sve.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/aba.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/abd.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/abdl.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/abs.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/add.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/addhn.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/addl.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/addl_high.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/addlv.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/addv.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/addw.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/addw_high.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/and.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/bcax.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/bic.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/bsl.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/cage.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/cagt.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/ceq.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/ceqz.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/cge.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/cgez.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/cgt.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/cgtz.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/cle.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/clez.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/cls.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/clt.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/cltz.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/clz.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/cmla.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/cmla_rot180.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/cmla_rot270.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/cmla_rot90.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/cnt.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/combine.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/create.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/cvt.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/dot.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/dot_lane.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/dup_lane.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/dup_n.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/eor.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/ext.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/fma.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/fma_lane.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/fma_n.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/get_high.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/get_lane.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/get_low.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/hadd.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/hsub.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/ld1.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/ld1_dup.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/ld1_lane.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/ld2.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/ld3.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/ld4.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/ld4_lane.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/max.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/maxnm.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/maxv.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/min.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/minnm.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/minv.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/mla.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/mla_n.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/mlal.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/mlal_high.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/mlal_high_n.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/mlal_lane.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/mlal_n.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/mls.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/mls_n.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/mlsl.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/mlsl_high.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/mlsl_high_n.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/mlsl_lane.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/mlsl_n.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/movl.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/movl_high.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/movn.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/movn_high.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/mul.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/mul_lane.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/mul_n.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/mull.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/mull_high.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/mull_lane.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/mull_n.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/mvn.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/neg.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/orn.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/orr.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/padal.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/padd.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/paddl.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/pmax.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/pmin.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/qabs.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/qadd.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/qdmulh.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/qdmulh_lane.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/qdmulh_n.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/qdmull.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/qmovn.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/qmovn_high.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/qmovun.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/qneg.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/qrdmulh.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/qrdmulh_lane.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/qrdmulh_n.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/qrshrn_n.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/qrshrun_n.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/qshl.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/qshlu_n.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/qshrn_n.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/qshrun_n.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/qsub.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/qtbl.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/qtbx.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/rbit.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/recpe.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/recps.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/reinterpret.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/rev16.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/rev32.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/rev64.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/rhadd.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/rnd.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/rndi.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/rndm.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/rndn.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/rndp.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/rshl.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/rshr_n.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/rshrn_n.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/rsqrte.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/rsqrts.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/rsra_n.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/set_lane.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/shl.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/shl_n.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/shll_n.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/shr_n.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/shrn_n.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/sqadd.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/sra_n.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/sri_n.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/st1.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/st1_lane.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/st2.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/st2_lane.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/st3.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/st3_lane.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/st4.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/st4_lane.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/sub.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/subhn.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/subl.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/subl_high.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/subw.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/subw_high.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/tbl.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/tbx.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/trn.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/trn1.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/trn2.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/tst.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/types.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/uqadd.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/uzp.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/uzp1.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/uzp2.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/xar.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/zip.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/zip1.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/neon/zip2.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/sve/add.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/sve/and.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/sve/cmplt.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/sve/cnt.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/sve/dup.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/sve/ld1.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/sve/ptest.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/sve/ptrue.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/sve/qadd.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/sve/reinterpret.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/sve/sel.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/sve/st1.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/sve/sub.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/sve/types.h" "${_IMPORT_PREFIX}/include/dep/simde/arm/sve/whilelt.h" "${_IMPORT_PREFIX}/include/dep/simde/mips/msa.h" "${_IMPORT_PREFIX}/include/dep/simde/mips/msa/add_a.h" "${_IMPORT_PREFIX}/include/dep/simde/mips/msa/adds.h" "${_IMPORT_PREFIX}/include/dep/simde/mips/msa/adds_a.h" "${_IMPORT_PREFIX}/include/dep/simde/mips/msa/addv.h" "${_IMPORT_PREFIX}/include/dep/simde/mips/msa/addvi.h" "${_IMPORT_PREFIX}/include/dep/simde/mips/msa/and.h" "${_IMPORT_PREFIX}/include/dep/simde/mips/msa/andi.h" "${_IMPORT_PREFIX}/include/dep/simde/mips/msa/ld.h" "${_IMPORT_PREFIX}/include/dep/simde/mips/msa/madd.h" "${_IMPORT_PREFIX}/include/dep/simde/mips/msa/st.h" "${_IMPORT_PREFIX}/include/dep/simde/mips/msa/subv.h" "${_IMPORT_PREFIX}/include/dep/simde/mips/msa/types.h" "${_IMPORT_PREFIX}/include/dep/simde/wasm/relaxed-simd.h" "${_IMPORT_PREFIX}/include/dep/simde/wasm/simd128.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx2.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/clmul.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/f16c.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/fma.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/gfni.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/mmx.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/sse.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/sse2.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/sse3.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/sse4.1.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/sse4.2.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/ssse3.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/svml.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/xop.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/2intersect.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/4dpwssd.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/4dpwssds.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/abs.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/add.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/adds.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/and.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/andnot.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/avg.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/bitshuffle.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/blend.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/broadcast.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/cast.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/cmp.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/cmpeq.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/cmpge.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/cmpgt.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/cmple.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/cmplt.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/cmpneq.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/compress.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/conflict.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/copysign.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/cvt.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/cvts.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/cvtt.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/dbsad.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/div.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/dpbf16.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/dpbusd.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/dpbusds.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/dpwssd.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/dpwssds.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/expand.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/extract.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/fixupimm.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/fixupimm_round.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/flushsubnormal.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/fmadd.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/fmsub.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/fnmadd.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/fnmsub.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/insert.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/kshift.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/load.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/loadu.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/lzcnt.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/madd.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/maddubs.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/max.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/min.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/mov.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/mov_mask.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/movm.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/mul.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/mulhi.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/mulhrs.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/mullo.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/multishift.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/negate.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/or.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/packs.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/packus.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/permutex2var.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/permutexvar.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/popcnt.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/range.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/range_round.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/rol.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/rolv.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/ror.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/rorv.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/round.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/roundscale.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/roundscale_round.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/sad.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/scalef.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/set.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/set1.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/set4.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/setone.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/setr.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/setr4.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/setzero.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/shldv.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/shuffle.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/sll.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/slli.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/sllv.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/sqrt.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/sra.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/srai.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/srav.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/srl.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/srli.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/srlv.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/store.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/storeu.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/sub.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/subs.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/ternarylogic.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/test.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/testn.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/types.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/unpackhi.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/unpacklo.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/xor.h" "${_IMPORT_PREFIX}/include/dep/simde/x86/avx512/xorsign.h" "${_IMPORT_PREFIX}/include/dep/speex/speex_echo.h" "${_IMPORT_PREFIX}/include/dep/speex/speex_jitter.h" "${_IMPORT_PREFIX}/include/dep/speex/speex_preprocess.h" "${_IMPORT_PREFIX}/include/dep/speex/speex_resampler.h" "${_IMPORT_PREFIX}/include/dep/speex/speexdsp_config_types.h" "${_IMPORT_PREFIX}/include/dep/speex/speexdsp_types.h"
  )
else()
  set_property(TARGET rack::dep
    APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
      "${_IMPORT_PREFIX}/include/dep"
  )
endif()

# Load information for each installed configuration.
file(GLOB _cmake_config_files "${CMAKE_CURRENT_LIST_DIR}/rack-dep-targets-*.cmake")
foreach(_cmake_config_file IN LISTS _cmake_config_files)
  include("${_cmake_config_file}")
endforeach()
unset(_cmake_config_file)
unset(_cmake_config_files)

# Cleanup temporary variables.
set(_IMPORT_PREFIX)

# Loop over all imported files and verify that they actually exist
foreach(_cmake_target IN LISTS _cmake_import_check_targets)
  if(CMAKE_VERSION VERSION_LESS "3.28"
      OR NOT DEFINED _cmake_import_check_xcframework_for_${_cmake_target}
      OR NOT IS_DIRECTORY "${_cmake_import_check_xcframework_for_${_cmake_target}}")
    foreach(_cmake_file IN LISTS "_cmake_import_check_files_for_${_cmake_target}")
      if(NOT EXISTS "${_cmake_file}")
        message(FATAL_ERROR "The imported target \"${_cmake_target}\" references the file
   \"${_cmake_file}\"
but this file does not exist.  Possible reasons include:
* The file was deleted, renamed, or moved to another location.
* An install or uninstall procedure did not complete successfully.
* The installation package was faulty and contained
   \"${CMAKE_CURRENT_LIST_FILE}\"
but not all the files it references.
")
      endif()
    endforeach()
  endif()
  unset(_cmake_file)
  unset("_cmake_import_check_files_for_${_cmake_target}")
endforeach()
unset(_cmake_target)
unset(_cmake_import_check_targets)

# This file does not depend on other imported targets which have
# been exported from the same project but in a separate export set.

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
cmake_policy(POP)
