/*
 * TRexVacuumChamberSphere.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexVacuumChamberSphere.hh"
#include "TRex/TRexSettings.hh"

#include <G4SystemOfUnits.hh>

TRexVacuumChamberSphere::TRexVacuumChamberSphere() {
}

TRexVacuumChamberSphere::~TRexVacuumChamberSphere() {
	// TODO Auto-generated destructor stub
}

void TRexVacuumChamberSphere::ConstructChamber(G4LogicalVolume* experimentalHall_log) {
	G4Material* chamberMaterial = TRexMaterials::Get()->GetMaterial("aluminium");

	/*	Chamber.WallThickness:	2.
		Chamber.InnerRadius:	98.
		Chamber.Length:		70.
		Chamber.FrontThickness:	10.
		Chamber.BackThickness:	2.

		Chamber.Flange.ConnectionThickness:		3.
		Chamber.Flange.Forward.InnerRadius:		20.
		Chamber.Flange.Forward.OuterRadius:		40.
		Chamber.Flange.Forward.Length:			10.
		Chamber.Flange.Forward.ConnectionLength:	10.
		Chamber.Flange.Backward.InnerRadius:		70.
		Chamber.Flange.Backward.OuterRadius:		85.
		Chamber.Flange.Backward.Length:			10.
		Chamber.Flange.Backward.ConnectionLength:	30.
		Chamber.Flange.Target.InnerRadius:		20.25
		Chamber.Flange.Target.OuterRadius:		27.5
		Chamber.Flange.Target.Length:			3.
		Chamber.Flange.Target.ConnectionLength:		27. */

	// commented values: T-REX spherical vaccum chamber
	// current values: adapted to Coulex chamber
	G4double chamberInnerRadius = 81. * mm;// 98. * mm;
	G4double chamberWallThickness = 2. * mm;

	G4double chamberForwardFlangeInnerRadius = 20. * mm;
	G4double chamberForwardFlangeOuterRadius = 40. * mm;
	G4double chamberForwardFlangeConnectionLength = 10. * mm;
	G4double chamberForwardFlangeLength = 10. * mm;

	G4double chamberBackwardFlangeInnerRadius = 50. * mm; //70. * mm;
	G4double chamberBackwardFlangeOuterRadius = 65. * mm; //85. * mm;
	G4double chamberBackwardFlangeConnectionLength = 30. * mm;
	G4double chamberBackwardFlangeLength = 10. * mm;

	G4double chamberFlangeConnectionThickness = 3. * mm;

	G4double chamberTargetFlangeInnerRadius = 20.25 *mm;
	G4double chamberTargetFlangeOuterRadius = 27.5 *mm;
	G4double chamberTargetFlangeConnectionLength = 27. * mm;
	G4double chamberTargetFlangeLength = 3. * mm;

	//the sphere
	G4Sphere* chamber_sphere;

	if(TRexSettings::Get()->VisualizationCut()){
		chamber_sphere = new G4Sphere("ChamberSphere", chamberInnerRadius, chamberInnerRadius + chamberWallThickness,
				270.*degree, 180.*degree, asin(chamberBackwardFlangeInnerRadius / chamberInnerRadius),
				180.*degree - asin(chamberBackwardFlangeInnerRadius / chamberInnerRadius) - asin(chamberForwardFlangeInnerRadius / chamberInnerRadius));
	}
	else{
		chamber_sphere = new G4Sphere("ChamberSphere", chamberInnerRadius, chamberInnerRadius + chamberWallThickness,
				0.*degree, 360.*degree, asin(chamberBackwardFlangeInnerRadius / chamberInnerRadius),
				180.*degree - asin(chamberBackwardFlangeInnerRadius / chamberInnerRadius) - asin(chamberForwardFlangeInnerRadius / chamberInnerRadius));
	}

	//flanges and connections to flanges
	G4Polycone* forward_flange;
	G4Polycone* backward_flange;

	G4double forward_flange_z[4] = {0, -chamberForwardFlangeConnectionLength, -chamberForwardFlangeConnectionLength,
		-(chamberForwardFlangeConnectionLength + chamberForwardFlangeLength)};
	G4double forward_flange_inner_radius[4] = {chamberForwardFlangeInnerRadius, chamberForwardFlangeInnerRadius,
		chamberForwardFlangeInnerRadius, chamberForwardFlangeInnerRadius};
	G4double forward_flange_outer_radius[4] = {chamberForwardFlangeInnerRadius + chamberFlangeConnectionThickness,
		chamberForwardFlangeInnerRadius + chamberFlangeConnectionThickness, chamberForwardFlangeOuterRadius, chamberForwardFlangeOuterRadius};

	G4double backward_flange_z[4] = {0, chamberBackwardFlangeConnectionLength, chamberBackwardFlangeConnectionLength,
		chamberBackwardFlangeConnectionLength + chamberBackwardFlangeLength};
	G4double backward_flange_inner_radius[4] = {chamberBackwardFlangeInnerRadius, chamberBackwardFlangeInnerRadius,
		chamberBackwardFlangeInnerRadius, chamberBackwardFlangeInnerRadius};
	G4double backward_flange_outer_radius[4] = {chamberBackwardFlangeInnerRadius + chamberFlangeConnectionThickness,
		chamberBackwardFlangeInnerRadius + chamberFlangeConnectionThickness, chamberBackwardFlangeOuterRadius, chamberBackwardFlangeOuterRadius};


	//flanges
	if(TRexSettings::Get()->VisualizationCut()){
		forward_flange = new G4Polycone("forward_flange",270.*degree,180.*degree,4,forward_flange_z,forward_flange_inner_radius,forward_flange_outer_radius);
		backward_flange = new G4Polycone("backward_flange",270.*degree,180.*degree,4,backward_flange_z,backward_flange_inner_radius,backward_flange_outer_radius);
	}
	else{
		forward_flange = new G4Polycone("forward_flange",0.,2*M_PI,4,forward_flange_z,forward_flange_inner_radius,forward_flange_outer_radius);
		backward_flange = new G4Polycone("backward_flange",0.,2*M_PI,4,backward_flange_z,backward_flange_inner_radius,backward_flange_outer_radius);
	}

	//union of sphere with forward flange
	G4UnionSolid* tmp_solid;
	tmp_solid = new G4UnionSolid("tmp_solid",chamber_sphere,forward_flange,new G4RotationMatrix(),
			G4ThreeVector(0,0,-sqrt(pow(chamberInnerRadius,2)-pow(chamberForwardFlangeInnerRadius,2))));


	//union of sphere with backward flange
	G4UnionSolid* chamber_with_flanges;
	chamber_with_flanges = new G4UnionSolid("chamber_with_flanges",tmp_solid,backward_flange,new G4RotationMatrix(),
			G4ThreeVector(0,0,sqrt(pow(chamberInnerRadius,2)-pow(chamberBackwardFlangeInnerRadius,2))));


	//hole for target flange
	G4Tubs* hole;
	hole = new G4Tubs("hole",0, chamberTargetFlangeInnerRadius, chamberWallThickness,0.,2*M_PI);

	//target flange
	G4Polycone* target_flange;

	G4double target_flange_z[4] = {0,
		-(chamberTargetFlangeConnectionLength - sin(20.*degree) * (chamberTargetFlangeOuterRadius - chamberTargetFlangeInnerRadius + chamberWallThickness)),
		-chamberTargetFlangeConnectionLength, -(chamberTargetFlangeConnectionLength + chamberTargetFlangeLength)};
	G4double target_flange_inner_radius[4] = {chamberTargetFlangeInnerRadius, chamberTargetFlangeInnerRadius,
		chamberTargetFlangeInnerRadius, chamberTargetFlangeInnerRadius};
	G4double target_flange_outer_radius[4] = {chamberTargetFlangeInnerRadius + chamberWallThickness,
		chamberTargetFlangeInnerRadius + chamberWallThickness,  chamberTargetFlangeOuterRadius, chamberTargetFlangeOuterRadius};


	if(TRexSettings::Get()->VisualizationCut()){
		target_flange = new G4Polycone("target_flange",270.*degree,180.*degree,4,target_flange_z,target_flange_inner_radius,target_flange_outer_radius);
	}
	else{
		target_flange = new G4Polycone("target_flange",0.,2*M_PI,4,target_flange_z,target_flange_inner_radius,target_flange_outer_radius);
	}

	//cut hole into sphere
	G4RotationMatrix* rotate_target_flange;
	rotate_target_flange = new G4RotationMatrix();
	rotate_target_flange->rotateX(90.*degree);

	G4SubtractionSolid* chamber_with_hole;
	chamber_with_hole = new G4SubtractionSolid("chamber_with_hole", chamber_with_flanges, hole, rotate_target_flange,
			G4ThreeVector(0,-(chamberInnerRadius + chamberWallThickness) + 2.*chamberWallThickness,0));



	//union of sphere with target flange
	G4UnionSolid* chamber_solid;
	chamber_solid = new G4UnionSolid("chamber_solid",chamber_with_hole,target_flange,rotate_target_flange,
			G4ThreeVector(0,-sqrt(pow((chamberInnerRadius + chamberWallThickness),2) - pow(chamberTargetFlangeOuterRadius,2)),0));


	G4LogicalVolume* chamber_log = new G4LogicalVolume(chamber_solid, chamberMaterial, "chamber_log");
	new G4PVPlacement(0, G4ThreeVector(0,0,0), chamber_log, "chamber", experimentalHall_log, false, 0);

	// grey color
	//chamber_log->SetVisAttributes(new G4VisAttributes(true, G4Colour(0.7,0.7,0.7)));
	chamber_log->SetVisAttributes(TRexColour::Get()->gray);
	//chamber_log->SetVisAttributes(TRexColour::Get()->yellow);
}
