#ifndef __BARREL_HH
#define __BARREL_HH

#include <iostream>
#include <vector>
#include "TObject.h"
#include "Time.hh"

class Barrel : public TObject {
	public:
		Barrel() {
			ClearBarrel();
		}

		~Barrel() {
		}

		void ClearBarrel() {
			fTime = 0;
			fID = -1;
			fRear = -1;
			fEdet = -1;
			fMult = -1;
			fNeighbor = false;
			fStripNr.clear();
			fStripPos.clear();
		}

		//set
		void ID(int id) {
			fID = id;
		}

		void Time(MyTime_t time) {
			fTime = time;
		}
		
		void SetRear(double rear) {
			fRear = rear;
		}

		void SetStrip(int strip, double energy) {
			fStripNr.push_back(strip);
			fStripPos.push_back(energy);
		}

		void Set2Strips(int firststrip, double firstenergy, int secondstrip, double secondenergy, bool neighbor) {
			fStripNr.push_back(firststrip);
			fStripPos.push_back(firstenergy);
			fStripNr.push_back(secondstrip);
			fStripPos.push_back(secondenergy);
			fNeighbor = neighbor;
		}

		void SetEdet(double energy) {
			fEdet = energy;
		}

		void SetMult(int mult) {
			fMult = mult;
		}

		//get
		int GetID() {
			return fID;
		}

		double GetRear() {
			return fRear;
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

		bool GetNeighbor() {
			return fNeighbor;
		}

		std::vector<int> GetStripNr() {
			return fStripNr;
		}

		std::vector<double> GetStripPos() {
			return fStripPos;
		}

		long long SizeOf() {
			long long result = 0;
			result += sizeof(fRear);
			result += sizeof(fEdet);
			result += sizeof(fNeighbor);
			result += sizeof(fMult);
			result += fStripNr.size()*sizeof(int);
			result += fStripPos.size()*sizeof(double);
			return result;
		}



	protected:
		int fID;
		double fRear;
		double fEdet;
		int fMult;
		bool fNeighbor;
		std::vector<int> fStripNr;
		std::vector<double> fStripPos;
		MyTime_t fTime;

		ClassDef(Barrel, 1);
};

#endif
