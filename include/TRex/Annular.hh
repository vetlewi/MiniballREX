#ifndef __ANNULAR_HH
#define __ANNULAR_HH

#include <iostream>
#include <vector>
#include "TObject.h"

#include "Time.hh"

class Annular : public TObject {
	public:
		Annular() {
			ClearAnnular();
		}

		~Annular() {
		}

		void ClearAnnular() {
			fTime = 0;
			fID = -1;
			fEdet = -1;
			fMult = -1;
			fStripNr.clear();
			fStripEnergy.clear();
			fRingNr.clear();
			fRingEnergy.clear();
		}
		//set
		void ID(int id) {
			fID = id;
		}
		void Time(MyTime_t time) {
			fTime = time;
		}
		void SetEdet(double energy) {
			fEdet = energy;
		}

		void SetStrip(int strip, double energy) {
			fStripNr.push_back(strip);
			fStripEnergy.push_back(energy);
		}

		void Set2Strips(int firststrip, double firstenergy, int secondstrip, double secondenergy) {
			fStripNr.push_back(firststrip);
			fStripEnergy.push_back(firstenergy);
			fStripNr.push_back(secondstrip);
			fStripEnergy.push_back(secondenergy);
		}

		void SetRing(int ring, double energy) {
			fRingNr.push_back(ring);
			fRingEnergy.push_back(energy);
		}

		void Set2Rings(int firstring, double firstenergy, int secondring, double secondenergy) {
			fRingNr.push_back(firstring);
			fRingEnergy.push_back(firstenergy);
			fRingNr.push_back(secondring);
			fRingEnergy.push_back(secondenergy);
		}

		void SetMult(int mult) {
			fMult = mult;
		}

		//get
		int GetID() {
			return fID;
		}

		double GetEdet() {
			return fEdet;
		}

		int GetMult() {
			return fMult;
		}

		double GetTime() {
			return fTime;
		}

		std::vector<int> GetStripNr() {
			return fStripNr;
		}

		std::vector<double> GetStripEnergy() {
			return fStripEnergy;
		}

		std::vector<int> GetRingNr() {
			return fRingNr;
		}

		std::vector<double> GetRingEnergy() {
			return fRingEnergy;
		}

		long long SizeOf() {
			long long result = 0;
			result += sizeof(fEdet);
			result += fStripNr.size()*sizeof(int);
			result += fStripEnergy.size()*sizeof(double);
			result += fRingNr.size()*sizeof(int);
			result += fRingEnergy.size()*sizeof(double);
			return result;
		}

	protected:
		int fID;
		std::vector<int> fStripNr;
		std::vector<double> fStripEnergy;
		std::vector<int> fRingNr;
		std::vector<double> fRingEnergy;
		double fEdet;
		int fMult;
		MyTime_t fTime;

		ClassDef(Annular, 1);
};

#endif
