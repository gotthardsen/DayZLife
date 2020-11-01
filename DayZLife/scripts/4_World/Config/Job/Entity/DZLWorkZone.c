class DZLWorkZone
{
    vector position;
    float range;
    int timeToHarvestPerItemInSeconds;
    int damagePerHarvestItem;
    ref array<ref DZLHarvestItemToolRelation> harvestItemToolRelation;

    void DZLWorkZone(vector position, float range, string zoneDisplayName, int timeToHarvestPerItemInSeconds, int damagePerHarvestItem, array<ref DZLHarvestItemToolRelation> harvestItemToolRelation) {
        this.position = position;
        this.range = range;
        this.timeToHarvestPerItemInSeconds = timeToHarvestPerItemInSeconds;
        this.harvestItemToolRelation = harvestItemToolRelation;
    }
}