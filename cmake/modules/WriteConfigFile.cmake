 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
MACRO (WRITE_CONFIG_FILE filename)

  String(REGEX REPLACE "^.*(install).*$" "\\1" INSTALL_VERSION ${filename})
  String(COMPARE EQUAL "install" "${INSTALL_VERSION}" INSTALL_TRUE)

  List(REMOVE_ITEM LD_LIBRARY_PATH ${CMAKE_BINARY_DIR}/lib)

  If (INSTALL_TRUE)
    SET(_INSTALLDIR ${CMAKE_INSTALL_PREFIX})
    SET(_BINDIR ${CMAKE_INSTALL_PREFIX}/bin)
    SET(TAIGALIBDIR ${CMAKE_INSTALL_PREFIX}/lib)
    SET(_LD_LIBRARY_PATH ${TAIGALIBDIR} ${LD_LIBRARY_PATH})
  Else (INSTALL_TRUE)
    SET(_INSTALLDIR ${CMAKE_BINARY_DIR})
    SET(_BINDIR ${CMAKE_BINARY_DIR})
#    SET(VMCWORKDIR ${CMAKE_SOURCE_DIR})
    SET(TAIGALIBDIR ${CMAKE_BINARY_DIR}/lib)
    SET(_LD_LIBRARY_PATH ${TAIGALIBDIR} ${LD_LIBRARY_PATH})
  EndIf (INSTALL_TRUE)

  If(NOT DEFINED FULL_CONFIG_FILE)
    Set(FULL_CONFIG_FILE "true")
  EndIf(NOT DEFINED FULL_CONFIG_FILE)


  IF(CMAKE_SYSTEM_NAME MATCHES Linux)
    IF(TAIGAROOTPATH)
      configure_file(${TAIGAROOTPATH}/share/fairbase/cmake/scripts/check_system.sh.in
                     ${CMAKE_CURRENT_BINARY_DIR}/check_system.sh
                    )
      configure_file(${TAIGAROOTPATH}/share/fairbase/cmake/scripts/check_system.csh.in
                     ${CMAKE_CURRENT_BINARY_DIR}/check_system.csh
                    )
    ELSE(TAIGAROOTPATH)
      configure_file(${PROJECT_SOURCE_DIR}/cmake/scripts/check_system.sh.in
                     ${CMAKE_CURRENT_BINARY_DIR}/check_system.sh
                    )
      configure_file(${PROJECT_SOURCE_DIR}/cmake/scripts/check_system.csh.in
                     ${CMAKE_CURRENT_BINARY_DIR}/check_system.csh
                    )
    ENDIF(TAIGAROOTPATH)

    EXECUTE_PROCESS(COMMAND lsb_release -sd
                     OUTPUT_VARIABLE _linux_flavour
                     OUTPUT_STRIP_TRAILING_WHITESPACE
                    )

    IF(_linux_flavour)
      STRING(REGEX REPLACE "^\"" "" _linux_flavour ${_linux_flavour})
      STRING(REGEX REPLACE "\"$" "" _linux_flavour ${_linux_flavour})
    ENDIF(_linux_flavour)

    EXECUTE_PROCESS(COMMAND uname -m
                    OUTPUT_VARIABLE _system
                    OUTPUT_STRIP_TRAILING_WHITESPACE
                   )

  ElseIf(CMAKE_SYSTEM_NAME MATCHES Darwin)
    IF(TAIGAROOTPATH)
      configure_file(${TAIGAROOTPATH}/share/fairbase/cmake/scripts/check_system_mac.sh.in
                     ${CMAKE_CURRENT_BINARY_DIR}/check_system.sh
                    )
      configure_file(${TAIGAROOTPATH}/share/fairbase/cmake/scripts/check_system_mac.csh.in
                     ${CMAKE_CURRENT_BINARY_DIR}/check_system.csh
                    )
    ELSE(TAIGAROOTPATH)
      configure_file(${PROJECT_SOURCE_DIR}/cmake/scripts/check_system_mac.sh.in
                     ${CMAKE_CURRENT_BINARY_DIR}/check_system.sh
                    )
      configure_file(${PROJECT_SOURCE_DIR}/cmake/scripts/check_system_mac.csh.in
                     ${CMAKE_CURRENT_BINARY_DIR}/check_system.csh
                    )
    ENDIF(TAIGAROOTPATH)
    EXECUTE_PROCESS(COMMAND uname -sr
                    OUTPUT_VARIABLE _linux_flavour
                    OUTPUT_STRIP_TRAILING_WHITESPACE
                   )
    EXECUTE_PROCESS(COMMAND uname -m
                    OUTPUT_VARIABLE _system
                    OUTPUT_STRIP_TRAILING_WHITESPACE
                   )
  ENDIF(CMAKE_SYSTEM_NAME MATCHES Linux)


  CONVERT_LIST_TO_STRING(${ROOT_LIBRARY_DIR})
  Set(ROOT_LIBRARY_DIR ${output})

  CONVERT_LIST_TO_STRING(${ROOT_LIBRARIES})
  Set(ROOT_LIBRARIES ${output})

  CONVERT_LIST_TO_STRING(${ROOT_INCLUDE_DIR})
  Set(ROOT_INCLUDE_DIR ${output} )

  Set(TAIGALIBDIR ${TAIGALIBDIR})

  List(REMOVE_DUPLICATES _LD_LIBRARY_PATH)
  CONVERT_LIST_TO_STRING(${_LD_LIBRARY_PATH})

  IF(CMAKE_SYSTEM_NAME MATCHES Linux)
    Set(MY_LD_LIBRARY_PATH ${output})
  ELSE(CMAKE_SYSTEM_NAME MATCHES Linux)
    IF(CMAKE_SYSTEM_NAME MATCHES Darwin)
      Set(MY_DYLD_LIBRARY_PATH ${output})
    ENDIF(CMAKE_SYSTEM_NAME MATCHES Darwin)
  ENDIF(CMAKE_SYSTEM_NAME MATCHES Linux)

  Set(USE_VGM 1)

  SET (PATH ${ROOTSYS}/bin ${PATH})
  CONVERT_LIST_TO_STRING(${PATH})
  Set(MY_PATH ${output})

  If(FAIRSOFT_EXTERN)
    Set(PYTHIA8DATA "${SIMPATH}/share/pythia8/xmldoc")
  Else(FAIRSOFT_EXTERN)
    Set(PYTHIA8DATA "${SIMPATH}/generators/pythia8/xmldoc")
  EndIf(FAIRSOFT_EXTERN)

  CONVERT_LIST_TO_STRING($ENV{NEW_CLASSPATH})
  Set(MY_CLASSPATH ${output})

  CONVERT_LIST_TO_STRING(${ROOT_INCLUDE_PATH})
  Set(ROOT_INCLUDE_PATH ${output})

  IF(${filename} MATCHES "[.]csh.*$")
    IF(TAIGAROOTPATH)
    configure_file(${TAIGAROOTPATH}/share/fairbase/cmake/scripts/config.csh.in
	           ${CMAKE_CURRENT_BINARY_DIR}/${filename}
                  )
    ELSE(TAIGAROOTPATH)
    configure_file(${PROJECT_SOURCE_DIR}/cmake/scripts/config.csh.in
	           ${CMAKE_CURRENT_BINARY_DIR}/${filename}
                  )
    ENDIF(TAIGAROOTPATH)


  ELSE(${filename} MATCHES "[.]csh.*$")
    IF(TAIGAROOTPATH)
    configure_file(${TAIGAROOTPATH}/share/fairbase/cmake/scripts/config.sh.in
	           ${CMAKE_CURRENT_BINARY_DIR}/${filename}
                  )
    ELSE(TAIGAROOTPATH)
    configure_file(${PROJECT_SOURCE_DIR}/cmake/scripts/config.sh.in
	           ${CMAKE_CURRENT_BINARY_DIR}/${filename}
                  )
    ENDIF(TAIGAROOTPATH)

  ENDIF(${filename} MATCHES "[.]csh.*$")


ENDMACRO (WRITE_CONFIG_FILE)


MACRO (CONVERT_LIST_TO_STRING)

  set (tmp "")
  foreach (_current ${ARGN})

    set(tmp1 ${tmp})
    set(tmp "")
    set(tmp ${tmp1}:${_current})

  endforeach (_current ${ARGN})
  If(tmp)
    STRING(REGEX REPLACE "^:(.*)" "\\1" output ${tmp})
  Else(tmp)
    Set(output "")
  EndIf(tmp)

ENDMACRO (CONVERT_LIST_TO_STRING LIST)
