# Plot the (FE) efficiencies

import numpy as np
from matplotlib import pyplot as plt 
import pandas as pd
from scipy import interpolate

import sys
#sys.path.append('../efficiency/inbeam')
#from eff_exp_unc import Eff_exp

datafile = "Peaks_labr.dat"
#Eg[MeV?] 	 nEvents 	 nCounts 	 cntFE 	 cntSE 	 cntDE 	 cnt511 	 Rest RestwoTres
data = np.loadtxt(datafile)
# data[1:12,0] /=1000.
data =  data[np.lexsort(np.fliplr(data).T)] # sort by gamma energy

# df = pd.read_csv(datafile, index_col=None,header=0, sep= "\t")
# df=df.rename(columns={'# Eg[MeV?]':'Eg', 'cntCompt=Rest':'rest'})
# df=df.sort_values(by="Eg")
# # print list(df)
# data = df.as_matrix(columns=None)
# print data
# data = data[1:,:]

Eg = data[:,0]
nEvents = data[:,1]
FE = data[:,3] / nEvents
SE = (data[:,4]) / nEvents
DE = (data[:,5]) / nEvents
c511 = (data[:,6]) / nEvents
Rest = (data[:,7]) / nEvents
compton = Rest - c511
Eff_tot = FE + SE + DE + Rest
Eff_totWoThres = data[:,2] / nEvents
# Rest_WoThres = Eff_totWoThres - FE - SE - DE - c511
Rest_WoThres = data[:,8] / nEvents
# nCounts
# print data[4,8] +  nEvents[4] * FE[4] +SE[4] +DE[4]+c511[4]
# print data[4,2]

# print "cntFE peak: ", data[:,3]

fig, ax = plt.subplots()
# plt.errorbar(data[:,0], Eff_totWoThres, fmt="o", label="Eff_totWoThres, sim.")
plt.errorbar(data[:,0], Eff_tot, fmt="o-", label="total, sim.")
# plt.errorbar(data[:,0], compton, fmt="o", label="Eff_\"comp\", sim.")
plt.errorbar(data[:,0], FE, fmt="-o", label="FE, sim.")
plt.errorbar(data[:,0], SE, fmt="o-", label="SE, sim.")
# plt.errorbar(data[:,0], DE, fmt="o", label="Eff_DE, sim.")

# plt.errorbar(data[:,0], c511, fmt="o", label="Eff_c511, sim.")

# read experimental FWHMs
# x, y, yerr = Eff_exp(3623)
# plt.errorbar(x, y, yerr=yerr, fmt=">", label="Exp (29Si, Ex=3623 keV), scaled")
# x, y, yerr = Eff_exp(3067)
# plt.errorbar(x, y, yerr=yerr, fmt="<", label="Exp (29Si, Ex=3067 keV), scaled")

# plt.xlabel(r'$E_\gamma$ [keV]',fontsize="large")
# plt.ylabel(r'Efficiency',fontsize="large")

# handles, labels = ax.get_legend_handles_labels()
# ax.legend(handles, labels, numpoints=1, loc =7)
# plt.savefig("Eff.png")
# plt.show()

###########
# print for folding.f in mama

from decimal import Decimal
def printFoldingArray(arr,arr_name, arr_number):
	for n, x in enumerate(arr):
	  if x<0: x=0
	  i=n+1
	  if i==1: print("      DATA " + arr_name + arr_number + "/\n"),
	  if i==1: print("     +   "),
	  if i!=(len(arr)): print('%.4E' % Decimal(x) +','),
	  else: print('%.4E' % Decimal(x) + "/"),
	  if i%7.==0 and i!=1 and i!=len(arr): print("\n     +   "),
	  if i==(len(arr)): print("\n"),
	for n, x in enumerate(arr):
		if x<0:
			print("! NOTE: Changed value of element ", + n, " to 0, because it was negative") 	


# Normalize Eff_tot to 1 at 1.33 MeV
Eff_tot1333 = np.interp(x=1333, xp=Eg, fp=Eff_tot)
Eff_tot /= Eff_tot1333

df_fwhm = pd.read_csv("resp_base.csv", comment="#", delim_whitespace=True)
fwhm_rel = interpolate.interp1d(df_fwhm.Eg, df_fwhm.FWHM_rel, kind='cubic', fill_value='extrapolate')


df = pd.DataFrame({"Eg": Eg,
				   "FWHM_rel_norm": fwhm_rel(Eg),
				   "Eff_tot": Eff_tot,
				   "FE": FE*nEvents,
				   "SE": SE*nEvents,
				   "DE": DE*nEvents,
				   "c511": c511*nEvents})
df.to_csv("resp_labr.csv", index=False)

arr_number = str(10)
#printFoldingArray(Eg, "ETAB", arr_number) # *1000 for MeV to keV
#printFoldingArray(Eff_tot, "FTAB",arr_number)
# printFoldingArray(Eff_tot*nEvents, "FTAB",arr_number)
#printFoldingArray(Eg, "Eg", arr_number)
#printFoldingArray(FE*nEvents, "FE", arr_number)
#printFoldingArray(SE*nEvents, "SE", arr_number)
#printFoldingArray(DE*nEvents, "DE",arr_number)
#printFoldingArray(c511*nEvents, "ANN",arr_number)
#printFoldingArray(Rest_WoThres*nEvents, "Compton(Name?)",arr_number)

#What does the ENA8 array contain?
# print np.interp(x=1332., xp=Eg, fp=FE)
# print np.interp(x=1779., xp=Eg, fp=FE)
# print np.interp(x=2028., xp=Eg, fp=FE)
# print np.interp(x=2838., xp=Eg, fp=FE)
# print np.interp(x=4496., xp=Eg, fp=FE)

