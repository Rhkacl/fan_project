# CMake 프로젝트에 AVR 플랫폼 설정
set(CMAKE_SYSTEM_NAME Generic)  # 시스템 이름을 'Generic'(범용)으로 설정
set(CMAKE_SYSTEM_PROCESSOR AVR) # 프로세서를 AVR 마이크로컨트롤러로 설정

# 타겟 MCU 설정 (2025.04.30 수정 사항)
set(MCU atmega128a) # 사용할 마이크로컨트롤러를 ATmega128A로 설정
set(CMAKE_C_FLAGS "-mmcu=${MCU}")    # MCU 설정
set(CMAKE_CXX_FLAGS "-mmcu=${MCU}") # C++ 컴파일러에 MCU 설정 플래그 전달

# AVR Toolchain 경로 설정
set(BINUTILS_PATH ${AVR_TOOLCHAIN_DIR}) # AVR 도구체인 루트 디렉토리 지정

# AVR Toolchain 실행 파일 경로 설정
set(TOOLCHAIN_PREFIX ${AVR_TOOLCHAIN_DIR}/bin/avr-) # AVR 컴파일러 및 유틸리티 파일 경로 접두사 설정

# CMake 테스트 빌드 대상 유형 설정
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY) # CMake의 테스트 컴파일을 정적 라이브러리로 제한

# 컴파일러 경로 설정
set(CMAKE_C_COMPILER "${TOOLCHAIN_PREFIX}gcc" CACHE FILEPATH "C Compiler path") # C 컴파일러 경로
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER}) # ASM(어셈블리) 컴파일러를 C 컴파일러와 동일하게 설정
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PREFIX}g++" CACHE FILEPATH "C++ Compiler path") # C++ 컴파일러 경로

# AVR에서 사용하는 추가 유틸리티 경로 설정
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy CACHE INTERNAL "objcopy tool") # 바이너리 변환 유틸리티 설정
set(CMAKE_SIZE_UTIL ${TOOLCHAIN_PREFIX}size CACHE INTERNAL "size tool") # 바이너리 크기 확인 유틸리티 설정

# C/C++ 표준 버전 설정
set(CMAKE_C_STANDARD    11) # C 언어 표준을 C11로 설정
set(CMAKE_CXX_STANDARD  11) # C++ 언어 표준을 C++11로 설정

# 컴파일러 확인 단계 비활성화
set(CMAKE_C_COMPILER_FORCED TRUE) # C 컴파일러 강제 사용 (검사 생략)
set(CMAKE_CXX_COMPILER_FORCED TRUE) # C++ 컴파일러 강제 사용 (검사 생략)

# 컴파일 및 링크 시 사용할 검색 경로 설정
set(CMAKE_FIND_ROOT_PATH ${BINUTILS_PATH})   # 검색 루트 경로를 도구체인 경로로 설정
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER) # 프로그램 검색 시 루트 경로 사용 안 함
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY) # 라이브러리 검색 시 루트 경로만 사용
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY) # 헤더 파일 검색 시 루트 경로만 사용
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY) # 패키지 검색 시 루트 경로만 사용