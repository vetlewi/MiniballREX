//
// Created by Vetle Wegner Ingeberg on 22/04/2020.
//

#ifndef OSLOLABR3ARRAY_H
#define OSLOLABR3ARRAY_H

#include <OsloLaBr/OCLLaBr3.hh>
#include <G4VUserDetectorConstruction.hh>

#include <G4Transform3D.hh>

class G4VPhysicalVolume;
class G4VisAttributes;


class MiniBallHistoManager;

class OsloLaBr3DetectorArray : public G4VUserDetectorConstruction
{

public:

    OsloLaBr3DetectorArray(MiniBallHistoManager* histoManager,
            G4VPhysicalVolume* mother, G4int nb_of_detectors,
            std::vector<std::string> name, std::vector<G4double> rho,
            std::vector<G4double> theta, std::vector<G4double> phi);

    ~OsloLaBr3DetectorArray() = default;


    G4VPhysicalVolume* Construct();

private:

    void GetTransformations(std::vector<G4double> &rho, std::vector<G4double> &theta,
                            std::vector<G4double> &phi, std::vector<G4double> spin);

    MiniBallHistoManager* histoManager;
    G4VPhysicalVolume* mother;

    G4int nb_of_detectors;
    std::vector<G4double> rho;
    std::vector<G4double> theta;
    std::vector<G4double> phi;
    std::vector<G4String> name;
    std::vector<G4Transform3D> transform;

    std::vector<OCLLaBr3*> detector;

};

#endif // OSLOLABR3ARRAY_H
