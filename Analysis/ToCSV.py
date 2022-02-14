


std::vector<double> GetEnergies(){
    std::vector<double> energies;
    energies.push_back(100);
    for ( int en = 200 ; en <= 10000 ; en += 200 ){
        energies.push_back(en);
    }
    return energies;
}


