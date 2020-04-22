#include "TRex/Germanium.hh"

void Germanium::SetCore(int crystal, double energy, MyTime_t time) {
	for(unsigned int i = 0; i < fCrystal.size(); ++i) {//check if crystal was already set
		//std::cout<<"fCrystal[i].GetCryID() "<<fCrystal[i].GetCryID()<<std::endl;
		if(crystal==fCrystal[i].GetCryID()) {
			//std::cout<<"Core "<<fClusterID<<" Crystal "<<i<<" was already set."<<std::endl;
			fCrystal[i].SetCore(energy, time);
			fStrange =1;
			return;
		}
	}
	//std::cout<<"Germanium::SetCore with crystal"<<crystal<<" energy "<<energy<<" time "<<time<<std::endl;

	fStrange =0;
	if(crystal <0 || crystal >2) {
		std::cout<<"crystal id in Germanium::SetCore "<<crystal<<", " <<energy<<", "<<time<<std::endl;
	}
	fCrystal.push_back(Crystal(crystal, energy, time));
}

void Germanium::SetSegment(int crystal, int segment, double energy, MyTime_t time) {
	if(crystal <0 || crystal >2) {
		std::cout<<"strange crystal id in Germanium::SetSegment "<<crystal<<std::endl;
	}

	for(unsigned int i = 0; i < fCrystal.size(); ++i) {//check if crystal was already set
		if(crystal==fCrystal[i].GetCryID()) {
			fCrystal[i].AddSegment(segment, energy, time);
			return;
		}
	}
	fCrystal.push_back(Crystal(crystal, segment, energy, time));
}

void Germanium::PrintCluster() {
	std::cout<<"size "<<fCrystal.size()<<std::endl;
	std::cout<<"Cluster ID\t"<<GetCluID()<<std::endl;
	for(unsigned int i = 0; i < fCrystal.size(); ++i) {
		std::cout<<"Crystal ID\t"<<fCrystal[i].GetCryID()<<"\tTime\t"<<fCrystal[i].GetTime()<<"\tCore Energy\t"<<fCrystal[i].GetCore()<<std::endl;
		for(unsigned int j = 0; j < fCrystal[i].GetSegID().size(); ++j) {
			std::cout<<"Segment ID\t"<<fCrystal[i].GetSegID()[j]<<"\tSegment Energy\t"<<fCrystal[i].GetSeg()[j]<<std::endl;
		}
	}
	std::cout<<"--------------------------------------------------"<<std::endl;

}

Crystal::Crystal(int crystal, double energy, MyTime_t time) {
	Clear();
	if(crystal <0 || crystal >2) {
		std::cout<<"crystal id in Crystal::Crystal(int crystal, double energy, MyTime_t time) "<<crystal<<", "<<energy<<", "<<time<<std::endl;
		std::cout<<"----------------------------------"<<std::endl;
	}
	SetCryID(crystal);
	SetCore(energy, time);
	//std::cout<<"Crystal::Crystal set to "<<GetCryID()<<" "<<GetCore()<<" keV "<<GetTime()<<std::endl;
}

Crystal::Crystal(int crystal, int segment, double energy, MyTime_t time) {
	Clear();
	if(crystal <0 || crystal >2) {
		std::cout<<"strange crystal id in Crystal::Crystal(int crystal, int segment, double energy, MyTime_t time) "<<crystal<<std::endl;
	}

	SetCryID(crystal);
	AddSegment(segment, energy, time);

}

void Crystal::SetCore(double energy, MyTime_t time) {
	//core
	if(fCoreEnergy>0.1) {
		//std::cout<<"Core Energy was already set to "<<fCoreEnergy<<" got new value "<<energy<<" not changing"<<std::endl;
		//std::cout<<"time was "<<fTime<<" new time "<<time<<" diff "<<fTime - time<<std::endl;
		return;
	}
	fCoreEnergy = energy;
	/*
		if(fTime>0.1 && time !=fTime) {
	//std::cout<<"Core Time was already set to "<<fTime<<" got new value "<<time<<" changing now. "<<std::endl;
	}
	*/
	fTime = time;
	//if(fTime<0.1 || fTime>1e15)
	//  std::cout<<"strange time "<<fTime<<std::endl;
	if(fTime>1e15) {
		std::cout<<"strange time "<<fTime<<std::endl;
	}
}

void Crystal::AddSegment(int segment, double energy, MyTime_t time) {
	//segment
	for(unsigned int i = 0; i < fSegID.size(); ++i) {//check if segment was already set
		if(segment == fSegID[i]) {
			std::cout<<"Segment "<<i<<" was already was already set to "<<fSegEnergy[i]<<" got new value of "<<energy<<" not changing."<<std::endl;
			return;
		}
	}
	fTime = time;
	fSegID.push_back(segment);
	fSegEnergy.push_back(energy);
}
