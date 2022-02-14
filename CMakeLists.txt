cmake_minimum_required(VERSION 3.15)
project(MiniballREX VERSION 0.7.0 LANGUAGES CXX)

# All build options
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)



#Make sure that custom modules are found
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)
include(LTO)


# Check for LTO support (needs to be after project(...) )
find_lto(CXX)
find_lto(C)

##############################################
# Find dependencies

#if (WITH_GEANT4_UIVIS)
    find_package(Geant4 REQUIRED ui_all vis_all)
#else()
#    find_package(Geant4 REQUIRED)
#endif()
include(${Geant4_USE_FILE})

if ( ${Geant4_multithreaded_FOUND} )
    message(INFO " Geant4 libraries are built with MT support")
    message(INFO " Geant4 include dir:"  ${Geant4_INCLUDE_DIRS})
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
endif()

message(INFO "Geant4 compile definitions:" ${Geant4_DEFINITIONS})

# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

find_package(ROOT CONFIG REQUIRED COMPONENTS RIO Net Hist Tree MathCore Physics)
#include("${ROOT_DIR}/modules/RootNewMacros.cmake")

find_package(Threads)

##############################################
# Create targets and set properties

add_library(CommandLineInterface SHARED STATIC
        src/CommandLineInterface/CommandLineInterface.cc
)

add_library(miniballrex::CommandLineInterface ALIAS CommandLineInterface)

target_include_directories(CommandLineInterface
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    )
target_enable_lto(CommandLineInterface optimized)

add_library(miniball SHARED
        src/Miniball/MiniBallCobalt60Source.cc
        src/Miniball/MiniBallDetectorArray.cc
        src/Miniball/MiniBallEuropium152Source.cc
        src/Miniball/MiniBallEventAction.cc
        src/Miniball/MiniBallGeom.cc
        src/Miniball/MiniBallHistoGenerator.cc
        src/Miniball/MiniBallHistoManager.cc
        src/Miniball/MiniBallHit.cc
        src/Miniball/MiniBallMaterial.cc
        src/Miniball/MiniBallRootGenerator.cc
        src/Miniball/MiniBallSensitiveDetector.cc
        src/Miniball/MiniBallSingleDetector.cc
        src/Miniball/MiniBallSource.cc
        src/Miniball/MiniBallTextGenerator.cc
        src/Miniball/MiniBallTrackInformation.cc
        src/Miniball/MiniBallTrackingAction.cc
        src/Miniball/MiniBallTripleDetector.cc
        src/Miniball/MiniBallWorld.cc
        )

add_library(miniballrex::miniball ALIAS miniball)

#target_compile_definitions(miniball PRIVATE ${Geant4_DEFINITIONS})

if (WITH_GEANT4_UIVIS)
    target_compile_definitions(miniball PRIVATE G4VIS_USE=1)
endif()

target_include_directories(miniball
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        ${Geant4_INCLUDE_DIRS}
        ${ROOT_INCLUDE_DIRS}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/Miniball
        )

target_link_libraries(miniball ${Geant4_LIBRARIES} ROOT::RIO ROOT::Hist ROOT::Tree ROOT::Physics)
target_enable_lto(miniball optimized)

add_library(OsloLaBr STATIC
        src/OsloLaBr/OCLLaBr3.cc
        src/OsloLaBr/OsloLaBr3Array.cc
        src/OsloLaBr/LaBrHit.cc
        src/OsloLaBr/OCLLaBr3SensitiveDetector.cc
)

add_library(miniballrex::OsloLaBr ALIAS OsloLaBr)
target_include_directories(OsloLaBr
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        ${Geant4_INCLUDE_DIRS}
        ${ROOT_INCLUDE_DIRS}
        PRIVATE
        ${CMAKE_SOURCE_DIR}/OsloLaBr
        )
target_link_libraries(OsloLaBr ${Geant4_LIBRARIES})
target_compile_definitions(OsloLaBr PRIVATE G4VIS_USE=1)
target_enable_lto(OsloLaBr optimized)

# Generate dictionary for TREX
root_generate_dictionary(G__trex
        ${CMAKE_SOURCE_DIR}/include/TRex/TRexSettings.hh
        ${CMAKE_SOURCE_DIR}/include/TRex/Barrel.hh
        ${CMAKE_SOURCE_DIR}/include/TRex/Annular.hh
        ${CMAKE_SOURCE_DIR}/include/TRex/Germanium.hh
        ${CMAKE_SOURCE_DIR}/include/TRex/ParticleMC.hh
    LINKDEF
        src/TRex/RootLinkDef.h)

add_library(trex SHARED
        src/TRex/Annular.cc
        src/TRex/Barrel.cc
        src/TRex/Element.cc
        src/TRex/Germanium.cc
        src/TRex/Isotopes.cc
        src/TRex/Kinematic.cc
        src/TRex/Material.cc
        src/TRex/ParticleMC.cc
        src/TRex/PhysicsList.cc
        src/TRex/PhysListEmStandard.cc
        src/TRex/TRexAlphaSource.cc
        src/TRex/TRexAngularDistribution.cc
        src/TRex/TRexBarrel.cc
        src/TRex/TRexBarrelDeltaE.cc
        src/TRex/TRexBarrelDeltaESingle.cc
        src/TRex/TRexBarrelDeltaESingleSensitiveDetector.cc
        src/TRex/TRexBarrelErest.cc
        src/TRex/TRexBarrelErestSingle.cc
        src/TRex/TRexBarrelErestSingleSensitiveDetector.cc
        src/TRex/TRexBaseDetector.cc
        src/TRex/TRexBaseGenerator.cc
        src/TRex/TRexBeam.cc
        src/TRex/TRexCD.cc
        src/TRex/TRexCDdeltaE.cc
        src/TRex/TRexCDdeltaESingle.cc
        src/TRex/TRexCDdeltaESingleSensitiveDetector.cc
        src/TRex/TRexCDErest.cc
        src/TRex/TRexCDErestSingle.cc
        src/TRex/TRexCDErestSingleSensitiveDetector.cc
        src/TRex/TRexColour.cc
        src/TRex/TRexData.cc
        src/TRex/TRexDetectorConstruction.cc
        src/TRex/TRexEventAction.cc
        src/TRex/TRexHit.cc
        src/TRex/TRexMaterials.cc
        src/TRex/TRexPrimaryGeneratorAction.cc
        src/TRex/TRexRunAction.cc
        src/TRex/TRexRutherford.cc
        src/TRex/TRexSettings.cc
        src/TRex/TRexTestSource.cc
        src/TRex/TRexTrapezoid.cc
        src/TRex/TRexTrapezoidDeltaE.cc
        src/TRex/TRexTrapezoidDeltaESingle.cc
        src/TRex/TRexTrapezoidDeltaESingleSensitiveDetector.cc
        src/TRex/TRexTrapezoidErest.cc
        src/TRex/TRexTrapezoidErestSingle.cc
        src/TRex/TRexTrapezoidErestSingleSensitiveDetector.cc
        src/TRex/TRexVacuumChamber.cc
        src/TRex/TRexVacuumChamberCylinder.cc
        src/TRex/TRexVacuumChamberGas.cc
        src/TRex/TRexVacuumChamberGasCylinder.cc
        src/TRex/TRexVacuumChamberGasSphere.cc
        src/TRex/TRexVacuumChamberSphere.cc
        G__trex
        src/TRex/TRexGammaSource.cpp)

add_library(miniballrex::trex ALIAS trex)

target_include_directories(trex
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        ${Geant4_INCLUDE_DIRS}
        ${ROOT_INCLUDE_DIRS}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/trex
)

target_link_libraries(trex PUBLIC
        miniballrex::CommandLineInterface
        miniballrex::miniball
        miniballrex::OsloLaBr
        ${Geant4_LIBRARIES}
        ROOT::RIO
        ROOT::Hist
        ROOT::Tree
        ROOT::Physics
)

target_compile_definitions(trex PRIVATE ${Geant4_DEFINITIONS})
target_enable_lto(trex optimized)

add_executable(MiniballTRex app/TRexGeant4.cc)
target_compile_definitions(MiniballTRex PRIVATE USE_MT=0)
target_link_libraries(MiniballTRex miniballrex::trex miniballrex::OsloLaBr)
target_enable_lto(MiniballTRex optimized)

add_executable(TreeToCSV app/TreeToCSV.cpp)
target_include_directories(TreeToCSV PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external)
target_link_libraries(TreeToCSV miniballrex::trex Threads::Threads)
target_enable_lto(TreeToCSV optimized)