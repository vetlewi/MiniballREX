/************************************************************************
 * \file MiniBallEuropium152Source.hh
 *
 * \class MiniBallEuropium152Source
 * \brief  simulation of a europium 152 source
 *
 * \author hans.boie@mpi-hd.mpg.de
 *
 ************************************************************************/

#include "Miniball/MiniBallEuropium152Source.hh"
#include <Randomize.hh>
#include <G4SystemOfUnits.hh>

MiniBallEuropium152Source::MiniBallEuropium152Source()
        : MiniBallSource()
{
    // generate level structure
    MiniBallSourceLevel* ground = new MiniBallSourceLevel(0.*keV, 0, PLUS);
    level_structure.push_back(ground);
    G4int level_id=0;
    G4int ground_id=level_id++;

    feeding = new MiniBallSourceLevel();

    // decay to 152Gd
    MiniBallSourceLevel* l344 = new MiniBallSourceLevel(344.282*keV, 2, PLUS);
    level_structure.push_back(l344);
    G4int l344_id = level_id++;

    feeding->decay.push_back(l344_id);
    feeding->prob.push_back(0.082);

    MiniBallSourceLevel* l615 = new MiniBallSourceLevel(615.416*keV, 0, PLUS);
    level_structure.push_back(l615);
    G4int l615_id = level_id++;

    MiniBallSourceLevel* l755 = new MiniBallSourceLevel(755.397*keV, 4, PLUS);
    level_structure.push_back(l755);
    G4int l755_id = level_id++;

    feeding->decay.push_back(l755_id);
    feeding->prob.push_back(0.0094);

    MiniBallSourceLevel* l930 = new MiniBallSourceLevel(930.582*keV, 2, PLUS);
    level_structure.push_back(l930);
    G4int l930_id = level_id++;

    feeding->decay.push_back(l930_id);
    feeding->prob.push_back(0.0030);

    MiniBallSourceLevel* l1109 = new MiniBallSourceLevel(1109.183*keV, 2, PLUS);
    level_structure.push_back(l1109);
    G4int l1109_id = level_id++;

    feeding->decay.push_back(l1109_id);
    feeding->prob.push_back(0.0029);

    MiniBallSourceLevel* l1123 = new MiniBallSourceLevel(1123.189*keV, 3, MINUS);
    level_structure.push_back(l1123);
    G4int l1123_id = level_id++;

    feeding->decay.push_back(l1123_id);
    feeding->prob.push_back(0.138);

    MiniBallSourceLevel* l1318 = new MiniBallSourceLevel(1318.37*keV, 2, PLUS);
    level_structure.push_back(l1318);
    G4int l1318_id = level_id++;

    feeding->decay.push_back(l1318_id);
    feeding->prob.push_back(0.00018);

    MiniBallSourceLevel* l1433 = new MiniBallSourceLevel(1433.975*keV, 3, PLUS);
    level_structure.push_back(l1433);
    G4int l1433_id = level_id++;

    feeding->decay.push_back(l1433_id);
    feeding->prob.push_back(0.0240);

    MiniBallSourceLevel* l1605 = new MiniBallSourceLevel(1605.629*keV, 2, PLUS);
    level_structure.push_back(l1605);
    G4int l1605_id = level_id++;

    feeding->decay.push_back(l1605_id);
    feeding->prob.push_back(0.0010);

    MiniBallSourceLevel* l1643 = new MiniBallSourceLevel(1643.425*keV, 2, MINUS);
    level_structure.push_back(l1643);
    G4int l1643_id = level_id++;

    feeding->decay.push_back(l1643_id);
    feeding->prob.push_back(0.0178);

    // decay structure
    l1643->AddDecay(l344_id, 1.626, E1);
    l1643->AddDecay(l930_id, 0.0959, E1);
    l1643->AddDecay(l1109_id, 0.0430);
    l1643->AddDecay(l1123_id, 0.0536);

    l1605->AddDecay(ground_id, 0.0075, E2);
    l1605->AddDecay(l344_id, 0.0327);
    l1605->AddDecay(l615_id, 0.0309, E2);
    l1605->AddDecay(l930_id, 0.0190, E2);

    l1433->AddDecay(l344_id, 1.710, E2);
    l1433->AddDecay(l755_id, 0.461, E2);
    l1433->AddDecay(l930_id, 0.1522, M1_E2, 0.24);
    l1433->AddDecay(l1109_id, 0.0751);

    l1318->AddDecay(l344_id, 0.0144, E2);
    l1318->AddDecay(l615_id, 0.0035);

    l1123->AddDecay(l344_id, 12.96, E1);
    l1123->AddDecay(l755_id, 0.83, E1);
    l1123->AddDecay(l930_id, 0.00688, E1);

    l1109->AddDecay(ground_id, 0.183, E2);
    l1109->AddDecay(l344_id, 0.175, E2);
    l1109->AddDecay(l615_id, 0.0094);

    l930->AddDecay(ground_id, 0.0730, E2);
    l930->AddDecay(l344_id, 0.459, E2);
    l930->AddDecay(l615_id, 0.0507);

    l755->AddDecay(l344_id, 2.231, E2);

    l615->AddDecay(l344_id, 0.0730, E2);

    l344->AddDecay(ground_id, 26.58, E2);

    // decay to 152Sm
    MiniBallSourceLevel* l121 = new MiniBallSourceLevel(121.7825*keV, 2, PLUS);
    level_structure.push_back(l121);
    G4int l121_id = level_id++;

    feeding->decay.push_back(l121_id);
    feeding->prob.push_back(0.019);

    MiniBallSourceLevel* l366 = new MiniBallSourceLevel(366.4814*keV, 4, PLUS);
    level_structure.push_back(l366);
    G4int l366_id = level_id++;

    feeding->decay.push_back(l366_id);
    feeding->prob.push_back(0.0085);

    MiniBallSourceLevel* l810 = new MiniBallSourceLevel(810.465*keV, 2, PLUS);
    level_structure.push_back(l810);
    G4int l810_id = level_id++;

    feeding->decay.push_back(l810_id);
    feeding->prob.push_back(0.0123);

    MiniBallSourceLevel* l963 = new MiniBallSourceLevel(963.376*keV, 1, MINUS);
    level_structure.push_back(l963);
    G4int l963_id = level_id++;

    MiniBallSourceLevel* l1022 = new MiniBallSourceLevel(1022.962*keV, 4, PLUS);
    level_structure.push_back(l1022);
    G4int l1022_id = level_id++;

    feeding->decay.push_back(l1022_id);
    feeding->prob.push_back(0.0023);

    MiniBallSourceLevel* l1041 = new MiniBallSourceLevel(1041.180*keV, 3, MINUS);
    level_structure.push_back(l1041);
    G4int l1041_id = level_id++;

    feeding->decay.push_back(l1041_id);
    feeding->prob.push_back(0.0006);

    MiniBallSourceLevel* l1085 = new MiniBallSourceLevel(1085.897*keV, 2, PLUS);
    level_structure.push_back(l1085);
    G4int l1085_id = level_id++;

    feeding->decay.push_back(l1085_id);
    feeding->prob.push_back(0.212);

    MiniBallSourceLevel* l1233 = new MiniBallSourceLevel(1233.876*keV, 3, PLUS);
    level_structure.push_back(l1233);
    G4int l1233_id = level_id++;

    feeding->decay.push_back(l1233_id);
    feeding->prob.push_back(0.172);

    MiniBallSourceLevel* l1292 = new MiniBallSourceLevel(1292.801*keV, 2, PLUS);
    level_structure.push_back(l1292);
    G4int l1292_id = level_id++;

    feeding->decay.push_back(l1292_id);
    feeding->prob.push_back(0.0062);

    MiniBallSourceLevel* l1371 = new MiniBallSourceLevel(1371.752*keV, 4, PLUS);
    level_structure.push_back(l1371);
    G4int l1371_id = level_id++;

    feeding->decay.push_back(l1371_id);
    feeding->prob.push_back(0.0093);

    MiniBallSourceLevel* l1529 = new MiniBallSourceLevel(1529.806*keV, 2, MINUS);
    level_structure.push_back(l1529);
    G4int l1529_id = level_id++;

    feeding->decay.push_back(l1529_id);
    feeding->prob.push_back(0.247);

    MiniBallSourceLevel* l1579 = new MiniBallSourceLevel(1579.427*keV, 3, MINUS);
    level_structure.push_back(l1579);
    G4int l1579_id = level_id++;

    feeding->decay.push_back(l1579_id);
    feeding->prob.push_back(0.0205);

    MiniBallSourceLevel* l1649 = new MiniBallSourceLevel(1649.927*keV, 2, MINUS);
    level_structure.push_back(l1649);
    G4int l1649_id = level_id++;

    feeding->decay.push_back(l1649_id);
    feeding->prob.push_back(0.0089);

    // decay structure
    l1649->AddDecay(l121_id, 0.265, E1);
    l1649->AddDecay(l810_id, 0.0165);
    l1649->AddDecay(l963_id, 0.0192);
    l1649->AddDecay(l1085_id, 0.468, E1);
    l1649->AddDecay(l1233_id, 0.1106);

    l1579->AddDecay(l121_id, 0.493, E1);
    l1579->AddDecay(l366_id, 1.399, E1);
    l1579->AddDecay(l810_id, 0.090);
    l1579->AddDecay(l963_id, 0.0090);
    l1579->AddDecay(l1022_id, 0.0190);
    l1579->AddDecay(l1041_id, 0.0042);
    l1579->AddDecay(l1085_id, 0.0313);
    l1579->AddDecay(l1371_id, 0.0044);

    l1529->AddDecay(l121_id, 20.87, E1);
    l1529->AddDecay(l810_id, 0.058, E1);
    l1529->AddDecay(l963_id, 0.1294, M1_E2, -0.74);
    l1529->AddDecay(l1041_id, 0.407, M1_E2, 5.6);
    l1529->AddDecay(l1085_id, 2.78, E1);
    l1529->AddDecay(l1233_id, 0.44, E1);

    l1371->AddDecay(l121_id, 0.184, E2);
    l1371->AddDecay(l366_id, 0.647, E2);
    l1371->AddDecay(l810_id, 0.00104);
    l1371->AddDecay(l1041_id, 0.0075);
    l1371->AddDecay(l1085_id, 0.0111);

    l1292->AddDecay(ground_id, 0.102);
    l1292->AddDecay(l121_id, 0.0357);
    l1292->AddDecay(l366_id, 0.265);
    l1292->AddDecay(l810_id, 0.0271, E2);
    l1292->AddDecay(l963_id, 0.1232);
    l1292->AddDecay(l1022_id, 0.0081);
    l1292->AddDecay(l1041_id, 0.0626);

    l1233->AddDecay(l121_id, 13.55, M1_E2, -8.7);
    l1233->AddDecay(l366_id, 4.15, M1_E2, -6.5);
    l1233->AddDecay(l810_id, 0.0027);
    l1233->AddDecay(l1085_id, 0.040);

    l1085->AddDecay(ground_id, 9.92, E2);
    l1085->AddDecay(l121_id, 14.34, E2);
    l1085->AddDecay(l366_id, 0.267, E2);
    l1085->AddDecay(l810_id, 0.0336);

    l1041->AddDecay(l121_id, 0.436, E1);
    l1041->AddDecay(l366_id, 0.167, E1);

    l1022->AddDecay(l121_id, 0.092, E2);
    l1022->AddDecay(l366_id, 0.1440, E2);
    l1022->AddDecay(l810_id, 0.0196, E2);

    l963->AddDecay(ground_id, 0.134, E1);
    l963->AddDecay(l121_id, 0.1628, E1);

    l810->AddDecay(ground_id, 0.317, E2);
    l810->AddDecay(l121_id, 0.835, E2);
    l810->AddDecay(l366_id, 0.313, E2);

    l366->AddDecay(l121_id, 7.49, E2);

    l121->AddDecay(ground_id, 28.4, E2);

    // set internal conversion coefficients
    SetInternalConversionCoeffE2(1.1716, 121.7825*keV);
    SetInternalConversionCoeffE2(0.1088, 244.6989*keV);
    SetInternalConversionCoeffE2(0.0397, 344.281*keV);

    // correct relative decay probabilities by conversion coefficients
    InternalConversionCorrectProbabilities();
}

MiniBallEuropium152Source::~MiniBallEuropium152Source()
{
    for(size_t q=0; q<level_structure.size(); q++)
        delete level_structure[q];
}


