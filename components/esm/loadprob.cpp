#include "loadprob.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void Probe::load(ESMReader &esm)
{
    mModel = esm.getHNString("MODL");
    mName = esm.getHNString("FNAM");

    esm.getHNT(mData, "PBDT", 16);

    mScript = esm.getHNOString("SCRI");
    mIcon = esm.getHNOString("ITEX");
}

void Probe::save(ESMWriter &esm)
{
    esm.writeHNCString("MODL", mModel);
    esm.writeHNCString("FNAM", mName);

    esm.writeHNT("PBDT", mData, 16);
    esm.writeHNOString("SCRI", mScript);
    esm.writeHNOCString("ITEX", mIcon);
}

    void Probe::blank()
    {
        mData.mWeight = 0;
        mData.mValue = 0;
        mData.mQuality = 0;
        mData.mUses = 0;
        mName.clear();
        mModel.clear();
        mIcon.clear();
        mScript.clear();
    }
}
