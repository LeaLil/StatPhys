#include "ParameterValidityChecker.h"

ParameterValidityChecker::ParameterValidityChecker(const MDParameters& parameters)
  : par(parameters){
    parametersValid = checkValidity();
}

bool ParameterValidityChecker::valid() const {
    return parametersValid;
}

std::string ParameterValidityChecker::getErrorMessage() const {
    return errorMessage;
}

bool ParameterValidityChecker::checkValidity() {
    if (par.boxSize[0] == 0 || par.boxSize[1] == 0 || par.boxSize[2] == 0) {
        errorMessage = "BoxSize(x/y/z) == 0";
        return false;
    }
    if (par.xvInitialization == InitialXVGenerator::generateInitialX && (par.numberAtomsOnBoxEdge[0] == 0 || par.numberAtomsOnBoxEdge[1] == 0 || par.numberAtomsOnBoxEdge[2] == 0)) {
        errorMessage = "XVInitialization == 0 and NAtomsOnBoxEdge(x/y/z) == 0";
        return false;
    }
    if (par.mdType == SimulationType::constantTemperature && par.temperatureCouplingTime <= 0) {
        errorMessage = "MDType == 1 and TemperatureCouplingTime <= 0";
        return false;
    }
    if (par.atomicMass <= 0) {
        errorMessage = "AtomicMass <= 0";
        return false;
    }
    if (2 * par.interactionCutoffRadius > par.boxSize[0] || 2 * par.interactionCutoffRadius > par.boxSize[1] || 2 * par.interactionCutoffRadius > par.boxSize[2]) {
        errorMessage = "2*InteractionCutoffRadius > BoxSize(x/y/z)";
        return false;
    }
    if (par.propertyPrintingInterval == 0 || par.trajectoryOutputInterval == 0) {
        errorMessage = "PropertyPrintingInterfval == 0 or TrajectoryOutputInterval == 0";
        return false;
    }
    if (par.numberRadialDistrPoints < 1) {
        errorMessage = "NumberRadialDistrPoints < 1";
        return false;
    }
    if (2 * par.radialDistrCutoffRadius > par.boxSize[0] || 2 * par.radialDistrCutoffRadius > par.boxSize[1] || 2 * par.radialDistrCutoffRadius > par.boxSize[2]) {
        errorMessage = "2*RadialDistrCutoffRadius > BoxSize(x/y/z)";
        return false;
    }
    if (par.initialTemperature >= 1e-6
        && (par.xvInitialization == InitialXVGenerator::xvFromAscii || par.xvInitialization == InitialXVGenerator::xvFromBinary)) {
        errorMessage = "Reading velocities from file but overwriting them (InitialTemperature >= 1e-6)";
        return false;
    }
    return true;
}
