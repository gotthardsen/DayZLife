class DZLWorkZones
{
	string version = "1";
    ref array<ref DZLWorkZone> workZones;

    void DZLWorkZones() {
        if (!Load()) {
            workZones = new array<ref DZLWorkZone>;
            array<ref DZLHarvestItemToolRelation> harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;
            array<string> itemsThatCanHarvest = new array<string>;
            array<string> itemsThatNeededForHarvest = new array<string>;


            if (DAY_Z_LIFE_DEBUG) {
                //Harvest Stone

                itemsThatCanHarvest.Insert("DZL_Stone");

                itemsThatNeededForHarvest.Insert("Pickaxe");

                DZLHarvestItemToolRelation relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
                harvestItemToolRelation.Insert(relation);

                DZLWorkZone zone = new DZLWorkZone(109, "4620 340 10360", 5, "Stone Mining Zone", 10, 2, harvestItemToolRelation, false);
                workZones.Insert(zone);
                //Harvest Stone end

                //Harvest Coal
                itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("DZL_Ore_Coal");

                itemsThatNeededForHarvest.Insert("Pickaxe");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
                harvestItemToolRelation.Insert(relation);

                zone = new DZLWorkZone(109, "4630 340 10360", 5, "Coal Mining Zone", 10, 2, harvestItemToolRelation);
                workZones.Insert(zone);
                //Harvest Coal end

                //Harvest Copper
                itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("DZL_Ore_Copper");

                itemsThatNeededForHarvest.Insert("Pickaxe");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
                harvestItemToolRelation.Insert(relation);

                zone = new DZLWorkZone(109, "4640 340 10360", 5, "Copper Mining Zone", 10, 2, harvestItemToolRelation);
                workZones.Insert(zone);
                //Harvest Copper end

                //Harvest Iron
                itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("DZL_Ore_Iron");

                itemsThatNeededForHarvest.Insert("Pickaxe");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
                harvestItemToolRelation.Insert(relation);

                zone = new DZLWorkZone(109, "4650 340 10360", 5, "Iron Mining Zone", 10, 2, harvestItemToolRelation);
                workZones.Insert(zone);
                //Harvest Iron end

                //Harvest Gold
                itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("DZL_Ore_Gold");

                itemsThatNeededForHarvest.Insert("Pickaxe");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
                harvestItemToolRelation.Insert(relation);

                zone = new DZLWorkZone(109, "4670 340 10360", 5, "Gold Mining Zone", 10, 2, harvestItemToolRelation);
                workZones.Insert(zone);
                //Harvest Gold end

                //Harvest Diamond
                itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("DZL_Ore_Diamond");

                itemsThatNeededForHarvest.Insert("Pickaxe");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
                harvestItemToolRelation.Insert(relation);

                zone = new DZLWorkZone(109, "4680 340 10360", 5, "Diamond Mining Zone", 10, 2, harvestItemToolRelation);
                workZones.Insert(zone);
                //Harvest Diamond end
            } else {
             // add life config;
                // Harvest Apple 1
                itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("Apple");

                itemsThatNeededForHarvest.Insert("CombatKnife");
                itemsThatNeededForHarvest.Insert("HuntingKnife");
                itemsThatNeededForHarvest.Insert("KitchenKnife");
                itemsThatNeededForHarvest.Insert("SteakKnife");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);

                harvestItemToolRelation.Insert(relation);

                zone = new DZLWorkZone(74, "7592 6 3483", 10, "#Apple_orchard", 4, 5, harvestItemToolRelation, true);
                workZones.Insert(zone);
                // Harvest Apple 1 end

                // Harvest Apple 2
                itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("Apple");

                itemsThatNeededForHarvest.Insert("CombatKnife");
                itemsThatNeededForHarvest.Insert("HuntingKnife");
                itemsThatNeededForHarvest.Insert("KitchenKnife");
                itemsThatNeededForHarvest.Insert("SteakKnife");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);

                harvestItemToolRelation.Insert(relation);

                zone = new DZLWorkZone(74, "12162 49 8984", 10, "#Apple_orchard", 4, 5, harvestItemToolRelation, true);
                workZones.Insert(zone);
                // Harvest Apple 2 end

                // Harvest Apple 3
                itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("Apple");

                itemsThatNeededForHarvest.Insert("CombatKnife");
                itemsThatNeededForHarvest.Insert("HuntingKnife");
                itemsThatNeededForHarvest.Insert("KitchenKnife");
                itemsThatNeededForHarvest.Insert("SteakKnife");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);

                harvestItemToolRelation.Insert(relation);

                zone = new DZLWorkZone(74, "11992 90 13926", 10, "#Apple_orchard", 4, 5, harvestItemToolRelation, true);
                workZones.Insert(zone);
                // Harvest Apple 3 end

                // Harvest Apple 4
                itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("Apple");

                itemsThatNeededForHarvest.Insert("CombatKnife");
                itemsThatNeededForHarvest.Insert("HuntingKnife");
                itemsThatNeededForHarvest.Insert("KitchenKnife");
                itemsThatNeededForHarvest.Insert("SteakKnife");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);

                harvestItemToolRelation.Insert(relation);

                zone = new DZLWorkZone(74, "2637 204 5381", 10, "#Apple_orchard", 4, 5, harvestItemToolRelation, true);
                workZones.Insert(zone);
                // Harvest Apple 4 end

                //Harvest Stone
                itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("DZL_Stone");

                itemsThatNeededForHarvest.Insert("Pickaxe");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
                harvestItemToolRelation.Insert(relation);

                zone = new DZLWorkZone(109, "13274 9 6095", 10, "#Stone_quarry", 10, 10, harvestItemToolRelation, true);
                workZones.Insert(zone);
                //Harvest Stone end

                //Harvest Coal
                itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("DZL_Ore_Coal");

                itemsThatNeededForHarvest.Insert("Pickaxe");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
                harvestItemToolRelation.Insert(relation);

                zone = new DZLWorkZone(109, "8722 99 13264", 10, "#coal_mine", 12, 10, harvestItemToolRelation, true);
                workZones.Insert(zone);
                //Harvest Coal end

                // Harvest Copper
                itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("DZL_Ore_Copper");

                itemsThatNeededForHarvest.Insert("Pickaxe");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
                harvestItemToolRelation.Insert(relation);

                zone = new DZLWorkZone(109, "8540 8 2978", 10, "#Copper_mine", 14, 10, harvestItemToolRelation, true);
                workZones.Insert(zone);
                // Harvest Copper end

                //Harvest Iron
                itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("DZL_Ore_Iron");

                itemsThatNeededForHarvest.Insert("Pickaxe");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
                harvestItemToolRelation.Insert(relation);

                zone = new DZLWorkZone(109, "919 180 6689", 10, "#Iron_mine", 16, 10, harvestItemToolRelation, true);
                workZones.Insert(zone);
                //Harvest Iron end

                //Harvest Gold
                itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("DZL_Ore_Gold");

                itemsThatNeededForHarvest.Insert("Pickaxe");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
                harvestItemToolRelation.Insert(relation);

                zone = new DZLWorkZone(109, "14098 2 13406", 10, "#Gold_mine", 18, 10, harvestItemToolRelation, true);
                workZones.Insert(zone);
                //Harvest Gold end

                //Harvest Diamond
                itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("DZL_Ore_Diamond");

                itemsThatNeededForHarvest.Insert("Pickaxe");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
                harvestItemToolRelation.Insert(relation);

                zone = new DZLWorkZone(109, "13672 49 12299", 10, "#Diamond_mine", 20, 10, harvestItemToolRelation, true);
                workZones.Insert(zone);
                //Harvest Diamond end

                //Harvest WoodenLog
                itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("DZL_WoodenLog");

                itemsThatNeededForHarvest.Insert("WoodAxe");
                itemsThatNeededForHarvest.Insert("FirefighterAxe");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
                harvestItemToolRelation.Insert(relation);

                zone = new DZLWorkZone(86, "932 180 7723", 10, "#Sawmill", 10, 5, harvestItemToolRelation, true);
                workZones.Insert(zone);
                //Harvest WoodenLog end

                // Harvest Cannabis
                itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("DZL_Cannabis");

                itemsThatNeededForHarvest.Insert("CombatKnife");
                itemsThatNeededForHarvest.Insert("HuntingKnife");
                itemsThatNeededForHarvest.Insert("KitchenKnife");
                itemsThatNeededForHarvest.Insert("SteakKnife");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);

                harvestItemToolRelation.Insert(relation);

                zone = new DZLWorkZone(74, "2227 433 15259", 10, "#Cannabis_plantation", 10, 10, harvestItemToolRelation, false);
                workZones.Insert(zone);
                // Harvest Cannabis end

                // Harvest Coca
                itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("DZL_Cocain");

                itemsThatNeededForHarvest.Insert("CombatKnife");
                itemsThatNeededForHarvest.Insert("HuntingKnife");
                itemsThatNeededForHarvest.Insert("KitchenKnife");
                itemsThatNeededForHarvest.Insert("SteakKnife");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);

                harvestItemToolRelation.Insert(relation);

                zone = new DZLWorkZone(74, "12115 140 15263", 10, "#Cocaine_plantation", 10, 10, harvestItemToolRelation, false);
                workZones.Insert(zone);
                // Harvest Coca end

                //Gather Vehicle Parts
                itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("DZL_Vehicle_Part_1");
                itemsThatCanHarvest.Insert("DZL_Vehicle_Part_2");
                itemsThatCanHarvest.Insert("DZL_Vehicle_Part_3");
                itemsThatCanHarvest.Insert("DZL_Vehicle_Part_4");
                itemsThatCanHarvest.Insert("DZL_Vehicle_Part_5");
                itemsThatCanHarvest.Insert("DZL_Vehicle_Part_6");
                itemsThatCanHarvest.Insert("DZL_Vehicle_Part_7");
                itemsThatCanHarvest.Insert("DZL_Vehicle_Part_8");
                itemsThatCanHarvest.Insert("DZL_Vehicle_Part_9");
                itemsThatCanHarvest.Insert("DZL_Vehicle_Part_10");
                itemsThatCanHarvest.Insert("DZL_Vehicle_Part_11");
                itemsThatCanHarvest.Insert("DZL_Vehicle_Part_12");
                itemsThatCanHarvest.Insert("DZL_Vehicle_Part_13");
                itemsThatCanHarvest.Insert("DZL_Vehicle_Part_14");
                itemsThatCanHarvest.Insert("DZL_Vehicle_Part_15");
                itemsThatCanHarvest.Insert("DZL_Vehicle_Part_16");
                itemsThatCanHarvest.Insert("DZL_Vehicle_Part_17");
                itemsThatCanHarvest.Insert("DZL_Vehicle_Part_18");
                itemsThatCanHarvest.Insert("DZL_Vehicle_Part_19");
                itemsThatCanHarvest.Insert("DZL_Vehicle_Part_20");

                itemsThatNeededForHarvest.Insert("Wrench");
                itemsThatNeededForHarvest.Insert("LugWrench");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
                harvestItemToolRelation.Insert(relation);

                zone = new DZLWorkZone(74, "12538 55 13790", 10, "#Scrap_yard", 15, 5, harvestItemToolRelation, true);
                workZones.Insert(zone);
                //Gather Vehicle Parts end

                // Ölschlamm
                itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("DZL_Oil_Barrel");

                itemsThatNeededForHarvest.Insert("FieldShovel");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);

                harvestItemToolRelation.Insert(relation);

                zone = new DZLWorkZone(90, "3765.302002 3.634198 2271.211914", 10, "Oilschlamm", 20, 10, harvestItemToolRelation, true);
                workZones.Insert(zone);
                // Ölschlamm ende
            }

            Save();
        }
    }

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "workZone.json")) {
            JsonFileLoader<DZLWorkZones>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "workZone.json", this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLWorkZones>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "workZone.json", this);
        }
    }
}