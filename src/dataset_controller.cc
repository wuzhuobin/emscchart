#include "dataset_controller.h"

emscchart::DatasetController::DatasetController(Chart const& chart,
                                                unsigned int dataset_index)
    : chart_(chart) {
  Initialize();
}

void emscchart::DatasetController::Initialize() {}
