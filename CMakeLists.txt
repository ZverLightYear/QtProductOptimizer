cmake_minimum_required(VERSION 3.17)
project(QtProductOptimizer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)
set(CMAKE_PREFIX_PATH /usr/include/x86_64-linux-gnu/qt5/)

add_executable(${PROJECT_NAME} main.cpp core/slicers/ISlicer.h core/MaterialContainer.cpp core/MaterialContainer.h core/Container.h core/slicers/NFDHSlicer.cpp core/slicers/NFDHSlicer.h core/sorters/IMaterialSorter.h core/sorters/DecreasingHeightSorter.cpp core/sorters/DecreasingHeightSorter.h core/IMaterial.h core/slicers/SliceResult.h core/Point.h core/RectMaterial.cpp core/RectMaterial.h core/slicers/FCNRSlicer.cpp core/slicers/FCNRSlicer.h core/slicers/SFSlicer.cpp core/slicers/SFSlicer.h core/slicers/FFDHSlicer.cpp core/slicers/FFDHSlicer.h core/slicers/Level.h UI/ParametersWindow.cpp UI/ParametersWindow.h UI/ParametersWindow.ui UI/GraphicWindow.cpp UI/GraphicWindow.h UI/GraphicWindow.ui UI/ProductEditWindow.cpp UI/ProductEditWindow.h UI/ProductEditWindow.ui core/slicers/BFDHSlicer.cpp core/slicers/BFDHSlicer.h core/ISliceManager.h core/RectSliceManager.cpp core/RectSliceManager.h core/slicers/ZESlicer.cpp core/slicers/ZESlicer.h core/slicers/ZEV2Slicer.cpp core/slicers/ZEV2Slicer.h core/sorters/DecreasingAreaSorter.cpp core/sorters/DecreasingAreaSorter.h)

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
