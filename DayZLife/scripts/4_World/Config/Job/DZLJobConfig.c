class DZLJobConfig
{
    ref array<ref DZLWorkZone> workZones;

    void DZLJobConfig() {
        if (!Load()) {
            workZones = new array<ref DZLWorkZone>;
            array<ref DZLHarvestItemToolRelation> harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;
            array<string> itemsThatCanHarvest = new array<string>;
            array<string> itemsThatNeededForHarvest = new array<string>;


			if (DAY_Z_LIFE_DEBUG) {
			    //first zone
                // First harvest
                itemsThatCanHarvest.Insert("Stone");
                itemsThatCanHarvest.Insert("SmallStone");
                itemsThatCanHarvest.Insert("SmallStone");
                itemsThatCanHarvest.Insert("SmallStone");

                itemsThatNeededForHarvest.Insert("Pickaxe");
                itemsThatNeededForHarvest.Insert("Sledgehammer");

                DZLHarvestItemToolRelation relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);

                harvestItemToolRelation.Insert(relation);
                // End First harvest
                // Second harvest
                itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;

                itemsThatCanHarvest.Insert("SmallStone");

                itemsThatNeededForHarvest.Insert("WoodAxe");
                itemsThatNeededForHarvest.Insert("FirefighterAxe");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
                harvestItemToolRelation.Insert(relation);

                // end Second harvest

                DZLWorkZone zone = new DZLWorkZone("12330 140 12666", 20, "Mining Zone", 10, 2, harvestItemToolRelation);
                workZones.Insert(zone);
                //end first zone
                // start second zone
                itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("Stone");
                itemsThatCanHarvest.Insert("SmallStone");
                itemsThatCanHarvest.Insert("SmallStone");
                itemsThatCanHarvest.Insert("SmallStone");

                itemsThatNeededForHarvest.Insert("Pickaxe");
                itemsThatNeededForHarvest.Insert("Sledgehammer");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);

                harvestItemToolRelation.Insert(relation);

                zone = new DZLWorkZone("12330 140 12666", 20, "Mining Zone", 10, 2, harvestItemToolRelation);
                workZones.Insert(zone);
                // end second zone
            } else {
             // add life config;
				// Harvest Apple 1
				itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;
				
				itemsThatCanHarvest.Insert("Apple");

				relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
				
                harvestItemToolRelation.Insert(relation);
				
				zone = new DZLWorkZone("7592 6 3483", 10, "Mining Zone", 10, 2, harvestItemToolRelation);
				workZones.Insert(zone);
				// Harvest Apple 1 end
				
				// Harvest Apple 2
				itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;
				
				itemsThatCanHarvest.Insert("Apple");
				
				relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
				
                harvestItemToolRelation.Insert(relation);
				
				zone = new DZLWorkZone("12162 49 8984", 10, "Mining Zone", 10, 2, harvestItemToolRelation);
				workZones.Insert(zone);
				// Harvest Apple 2 end
				
				// Harvest Apple 3
				itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;
				
				itemsThatCanHarvest.Insert("Apple");
				
				relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
				
                harvestItemToolRelation.Insert(relation);
				
				zone = new DZLWorkZone("11992 90 13926", 10, "Mining Zone", 10, 2, harvestItemToolRelation);
				workZones.Insert(zone);
				// Harvest Apple 3 end
				
				// Harvest Apple 4
				itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;
				
				itemsThatCanHarvest.Insert("Apple");
				
				relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
				
                harvestItemToolRelation.Insert(relation);
				
				zone = new DZLWorkZone("2637 204 5381", 10, "Mining Zone", 10, 2, harvestItemToolRelation);
				workZones.Insert(zone);
				// Harvest Apple 4 end
				
				//Harvest Stone
				itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("Stone");
                itemsThatCanHarvest.Insert("SmallStone");

                itemsThatNeededForHarvest.Insert("Pickaxe");
                itemsThatNeededForHarvest.Insert("Sledgehammer");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
                harvestItemToolRelation.Insert(relation);
				
				zone = new DZLWorkZone("6451 444 14747", 10, "Mining Zone", 10, 2, harvestItemToolRelation);
				workZones.Insert(zone);
				//Harvest Stone end
				
				//Harvest Copper
				itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("DZL_Ore_Copper");

                itemsThatNeededForHarvest.Insert("Pickaxe");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
                harvestItemToolRelation.Insert(relation);
				
				zone = new DZLWorkZone("8722 99 13264", 10, "Mining Zone", 10, 2, harvestItemToolRelation);
				workZones.Insert(zone);
				//Harvest Copper end
				
				//Harvest Coal
				itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("DZL_Ore_Coal");

                itemsThatNeededForHarvest.Insert("Pickaxe");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
                harvestItemToolRelation.Insert(relation);
				
				zone = new DZLWorkZone("8658 151 13630", 10, "Mining Zone", 10, 2, harvestItemToolRelation);
				workZones.Insert(zone);
				//Harvest Coal end
				
				//Harvest Iron
				itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("DZL_Ore_Iron");

                itemsThatNeededForHarvest.Insert("Pickaxe");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
                harvestItemToolRelation.Insert(relation);
				
				zone = new DZLWorkZone("8599 100 13337", 10, "Mining Zone", 10, 2, harvestItemToolRelation);
				workZones.Insert(zone);
				//Harvest Iron end
				
				//Harvest Silver
				itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("DZL_Ore_Silver");

                itemsThatNeededForHarvest.Insert("Pickaxe");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
                harvestItemToolRelation.Insert(relation);
				
				zone = new DZLWorkZone("916 181 6691", 10, "Mining Zone", 10, 2, harvestItemToolRelation);
				workZones.Insert(zone);
				//Harvest Silver end
				
				//Harvest Gold
				itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("DZL_Ore_Gold");

                itemsThatNeededForHarvest.Insert("Pickaxe");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
                harvestItemToolRelation.Insert(relation);
				
				zone = new DZLWorkZone("14103 2 13400", 10, "Mining Zone", 10, 2, harvestItemToolRelation);
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
				
				zone = new DZLWorkZone("13272 9 6090", 10, "Mining Zone", 10, 2, harvestItemToolRelation);
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
				
				zone = new DZLWorkZone("933 180 7723", 10, "Mining Zone", 10, 2, harvestItemToolRelation);
				workZones.Insert(zone);
				//Harvest WoodenLog end
				
				//Gather Vehicle Parts
				itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

                itemsThatCanHarvest.Insert("DZL_Scrap_1");
                itemsThatCanHarvest.Insert("DZL_Scrap_2");
                itemsThatCanHarvest.Insert("DZL_Scrap_3");
                itemsThatCanHarvest.Insert("DZL_Scrap_4");
                itemsThatCanHarvest.Insert("DZL_Scrap_5");
                itemsThatCanHarvest.Insert("DZL_Scrap_6");
                itemsThatCanHarvest.Insert("DZL_Scrap_7");
                itemsThatCanHarvest.Insert("DZL_Scrap_8");
                itemsThatCanHarvest.Insert("DZL_Scrap_9");
                itemsThatCanHarvest.Insert("DZL_Scrap_10");

                itemsThatNeededForHarvest.Insert("Wrench");
                itemsThatNeededForHarvest.Insert("LugWrench");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
                harvestItemToolRelation.Insert(relation);
				
				zone = new DZLWorkZone("12538 55 13790", 10, "Mining Zone", 10, 2, harvestItemToolRelation);
				workZones.Insert(zone);
				//Gather Vehicle Parts end
            }


			
		    Save();
        }
    }

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "workZone.json")) {
            JsonFileLoader<DZLJobConfig>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "workZone.json", this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLJobConfig>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "workZone.json", this);
        }
    }
}