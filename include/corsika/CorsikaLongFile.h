/**
   \file
   Reader for Corsika generated shower file

   \author Javier Gonzalez
   \version $Id$
   \date 14 Jul 2016
*/

#ifndef _corsika_CorsikaLongFile_h_
#define _corsika_CorsikaLongFile_h_

static const char CVSId_corsika_CorsikaLongFile[] =
"$Id$";

#include <string>
#include <map>
#include <vector>
#include <fstream>

#include <corsika/CorsikaLongProfile.h>

#include <boost/shared_ptr.hpp>

namespace corsika {


  /**
     \class CorsikaLongFile CorsikaLongFile.h "corsika/CorsikaLongFile.h"

     \brief Read data from .long files generated by CORSIKA

     \author Javier Gonzalez
     \date 14 Jul 2016
     \ingroup corsika
  */
  class CorsikaLongFile {
  public:
    CorsikaLongFile(std::string filename, double zenith=0.);
    ~CorsikaLongFile(){
      Close();
    }

    void Close() {
      if (fLongDataFile->is_open()) {fLongDataFile->close();}
    }

    CorsikaLongProfile GetProfile(int event);

    int size() const
    { return int(fN); }
    float Dx() const
    { return fDx; }
    bool HasParticleProfile() const
    { return fPartProfiles.size(); }
    bool HasEnergyDeposit() const
    { return fdEdXProfiles.size(); }
    bool IsSlantDepth() const
    { return fIsSlantDepthProfile; }

  private:
    void Scan();
    CorsikaLongProfile FetchProfile(int i);

    std::string fFilename;

    float fCosZenith;
    bool fIsSlantDepthProfile;
    float fN;
    float fDx;
    int fNBinsParticles;
    int fNBinsEnergyDeposit;

    boost::shared_ptr<std::ifstream> fLongDataFile;
    std::vector<std::streampos> fPartProfiles;
    std::vector<std::streampos> fdEdXProfiles;

  };

}

#endif

