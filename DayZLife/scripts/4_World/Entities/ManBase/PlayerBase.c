modded class PlayerBase
{
    ref DZLBuyHouseMenu houseBuyMenu;
    ref DZLUpgradeHouseMenu houseUpgradeMenu;
    ref DZLBankingMenu bankingMenu;
    ref DZLConfig config;
	ref DZLPlayerHouse house;
	ref DZLPlayer dzlPlayer;
	ref DZLBank dzlBank;
	ref DZLLicenceMenu licenceMenu;
	ref DZLProgressBar progressBar;

	bool IsDZLBank = false;
	bool IsLicencePoint = false;
	private int moneyPlayerIsDead = 0;
	bool IsRealPlayer = false;

	void ~PlayerBase() {
	    GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
	}

	override void Init() {
        super.Init();
        RegisterNetSyncVariableBool("IsDZLBank");
        RegisterNetSyncVariableBool("IsRealPlayer");
        RegisterNetSyncVariableBool("IsLicencePoint");
        RegisterNetSyncVariableInt("moneyPlayerIsDead", 0, 99999999999);
    }

    override void SetActions() {
        super.SetActions();

        AddAction(ActionOpenBuyHouseMenu);
        AddAction(ActionOpenUpgradeHouseMenu);
        AddAction(ActionOpenBankingMenu);
        AddAction(ActionRobMoney);
        AddAction(ActionRobBank);
        AddAction(ActionHarvestItem);
        AddAction(ActionOpenLicenseMenu);
        AddAction(ActionLicenceCrafting);

        if (GetGame().IsClient()) {
            GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
            Param1<PlayerBase> paramGetConfig = new Param1<PlayerBase>(this);
            GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_EVENT_GET_CONFIG, paramGetConfig, true);
            GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_GET_PLAYER_BUILDING, paramGetConfig, true);
            GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_PLAYER_DATA, paramGetConfig, true);
            GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_PLAYER_BANK_DATA, paramGetConfig, true);
        }
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE) {
            Param1 <ref DZLConfig> configParam;
            DebugMessageDZL("Initialize DZLConfig");
            if (ctx.Read(configParam)){
                this.config = configParam.param1;
                IsRealPlayer = true;
            }
        } else if (rpc_type == DAY_Z_LIFE_GET_PLAYER_BUILDING_RESPONSE) {
            Param1 <ref DZLPlayerHouse> houseParam;
            DebugMessageDZL("Initialize DZLPlayerHouse");
            if (ctx.Read(houseParam)){
                this.house = houseParam.param1;
            }
        } else if (rpc_type == DAY_Z_LIFE_PLAYER_DATA_RESPONSE) {
            Param1 <ref DZLPlayer> dzlPlayerParam;
            DebugMessageDZL("Initialize DZLPlayer");
            if (ctx.Read(dzlPlayerParam)){
                this.dzlPlayer = dzlPlayerParam.param1;
                UpdatePlayerAtDependencies();
            }
        } else if (rpc_type == DAY_Z_LIFE_PLAYER_BANK_DATA_RESPONSE) {
            Param1 <ref DZLBank> dzlBankParam;
            DebugMessageDZL("Initialize Bank");
            if (ctx.Read(dzlBankParam)){
                this.dzlBank = dzlBankParam.param1;
            }
        }
    }

    void UpdatePlayerAtDependencies() {
        if (houseBuyMenu && houseBuyMenu.IsVisible()) {
            houseBuyMenu.UpdatePlayer(this);;
        } else if (houseUpgradeMenu && houseUpgradeMenu.IsVisible()) {
            houseUpgradeMenu.UpdatePlayer(this);;
        } else if (bankingMenu && bankingMenu.IsVisible()) {
            bankingMenu.UpdatePlayer(this);;
        } else if (licenceMenu && licenceMenu.IsVisible()) {
            licenceMenu.UpdatePlayer(this);;
        }else if (progressBar && progressBar.IsVisible()) {
            progressBar.UpdatePlayer(this);;
        }
    }

    DZLBuyHouseMenu GetHouseBuyMenu(DZLHouseDefinition definition, Building target) {
        DebugMessageDZL("Initialize house buy menu");
        houseBuyMenu = new DZLBuyHouseMenu;
        InitMenu(houseBuyMenu);

		houseBuyMenu.SetHouseDefinition(definition);
		houseBuyMenu.SetTarget(target);

        return houseBuyMenu;
    }

    DZLUpgradeHouseMenu GetHouseUpgradeMenu(DZLHouseDefinition definition, Building target) {
        DebugMessageDZL("Initialize house upgrade menu");
        houseUpgradeMenu = new DZLUpgradeHouseMenu;
        InitMenu(houseUpgradeMenu);

		houseUpgradeMenu.SetHouseDefinition(definition);
		houseUpgradeMenu.SetTarget(target);

        return houseUpgradeMenu;
    }

    private void InitMenu(DZLBaseMenu menu) {
        menu.SetConfig(config);
        menu.SetPlayer(this);
    }

	DZLBankingMenu GetBankingMenu() {
		bankingMenu = DZLBankingMenu();
		InitMenu(bankingMenu);
		return bankingMenu;
	}

	DZLLicenceMenu GetLicenceMenu() {
		licenceMenu = DZLLicenceMenu();
		InitMenu(licenceMenu);
		return licenceMenu;
	}

    DZLProgressBar GetProgressBar() {
        progressBar = DZLProgressBar();
        progressBar.SetPlayer(this);
        return progressBar;
    }

	void CloseMenu() {
		if (houseBuyMenu && houseBuyMenu.IsVisible()) {
			houseBuyMenu.OnHide();
		} else if (houseUpgradeMenu && houseUpgradeMenu.IsVisible()) {
			houseUpgradeMenu.OnHide();
		} else if (bankingMenu && bankingMenu.IsVisible()) {
			bankingMenu.OnHide();
		} else if (licenceMenu && licenceMenu.IsVisible()) {
			licenceMenu.OnHide();
		} else if (progressBar && progressBar.IsVisible()) {
			progressBar.OnHide();
		}
	}

	DZLHouseDefinition FindHouseDefinition(Building building) {
		array<ref DZLHouseDefinition> houseConfigs = config.GetHouseDefinitions();
		foreach(DZLHouseDefinition definition: houseConfigs) {
                if (definition.houseType == building.GetType()) {
					return definition;
                }
            }
		return null;
	}

    void TransferFromDeadPlayer(DZLPlayer playerTarget) {
        playerTarget.AddMoneyToPlayer(moneyPlayerIsDead);
        moneyPlayerIsDead = 0;
    }

    float GetMoneyPlayerIsDead() {
        return moneyPlayerIsDead;
    }

    void SetMoneyPlayerIsDead(float money) {
        IsRealPlayer = false;
        moneyPlayerIsDead = money;
    }
	
	DZLLicence GetLicenceByPosition() {
        vector playerPosition = GetPosition();
        if (!playerPosition) {
            return null;
        }
		
        foreach(string licenceId: dzlPlayer.licenceIds) {
			DZLLicence licence = config.licenceConfig.licences.FindById(licenceId);
			
			if(!licence) continue;
			
            if (vector.Distance(licence.position, playerPosition) <= licence.range){
                return licence;
            }
        }
        return null;
    }
	
	string CanUseLicence(DZLLicence licence) {
        array<EntityAI> items = GetPlayerItems();
        map<string, int> craft = new map<string, int>;
        map<string, int> tools = new map<string, int>;
		string message = "";

        foreach(EntityAI item: items) {
            string itemType = item.GetType();
            itemType.ToLower();
			
			bool isCraft = false;
			foreach(DZLLicenceCraftItem craftItem: licence.craftItems) {
                if(IsNeededItem(craftItem, item, itemType)) {
					if (craft.Contains(itemType)) {
						craft.Set(itemType, craft.Get(itemType) + 1);
					} else {
						craft.Set(itemType, 1);
					}
					isCraft = true;
					break;
				}
			}
			
			if(isCraft) continue;
			
			foreach(DZLLicenceToolItem toolItem: licence.toolItems) {
                if(IsNeededItem(toolItem, item, itemType)) {
					if (tools.Contains(itemType)) {
						tools.Set(itemType, tools.Get(itemType) + 1);
					} else {
						tools.Set(itemType, 1);
					}
					break;
				}
			}
        }
		
		map<string, int> craftMap = licence.craftItems.GetTypeCountMap();
		map<string, int> toolMap = licence.toolItems.GetTypeCountMap();

		if (craft.Count() == craftMap.Count() && tools.Count() == toolMap.Count()) {
		    foreach(string type, int count: craftMap) {
				int countFound = 0;
				if (craft.Find(type, countFound)) {
					if (countFound <= count) {
						return "#not_enoug_items_to_craft";
					}
				} else {
					return "#missing_craft_item";
				}
			}
			

			foreach(string typeTool, int countTool: toolMap) {
                int countFoundTool = 0;
                if (tools.Find(typeTool, countFoundTool)) {
                    if (countFoundTool <= countTool) {
                        return "#not_enoug_tools_to_craft";
                    }
                } else {
                    return "#missing_tool_item";
                }
            }
		} else {
			message = "#has_not_found_all_items_that_is_needed_to_craft";
		}

        return message;
	}

	void UseLicence(DZLLicence licence) {
        array<EntityAI> items = GetPlayerItems();
        map<string, int> craftMap = licence.craftItems.GetTypeCountMap();
        map<string, int> toolMap = licence.toolItems.GetTypeCountMap();

		string message = "";

        foreach(EntityAI item: items) {
			if (craftMap.Count() == 0 && toolMap.Count() == 0) break;
			
            string itemType = item.GetType();
            itemType.ToLower();

			bool isCraft = false;
			foreach(DZLLicenceCraftItem craftItem: licence.craftItems) {
				if (craftMap.Count() == 0) break;
				
                if(IsNeededItem(craftItem, item, itemType)) {
					int countFoundCraft = 0;
					if(craftMap.Find(itemType, countFoundCraft)) {
						int quant = item.GetQuantity();
						
						if (quant == -1) {
							GetGame().ObjectDelete(item);
							craftMap.Remove(itemType);
						} else if (quant > countFoundCraft) {
							ItemBase.Cast(item).SetQuantity(quant - countFoundCraft);
							
							craftMap.Remove(itemType);
						} else {
							countFoundCraft -= quant;
							GetGame().ObjectDelete(item);
							craftMap.Set(itemType, countFoundCraft);
						}
						isCraft = true;
						break;
					}
				}
			}

			if(isCraft) continue;

			foreach(DZLLicenceToolItem toolItem: licence.toolItems) {
				if (toolMap.Count() == 0) break;
				
                if(IsNeededItem(toolItem, item, itemType)) {
					int countFoundTool = 0;
					if(toolMap.Find(itemType, countFoundTool)) {
					    int health = item.GetHealth();
						
						if (health >= toolItem.damageToTool) {
							craftMap.Remove(itemType);
							item.SetHealth(item.GetHealth() - toolItem.damageToTool);
						}
						break;
					    
					}
				}
			}
        }
	}

	private bool IsNeededItem(DZLLicenceCraftItem item, EntityAI itemSearch, string ItemSearchType) {
        if(item.GetLowerCaseType() == ItemSearchType) {
            if(GetGame().IsServer()) {
                if (itemSearch.GetHealth() >= item.health && itemSearch.GetQuantity() >= item.quantity) {
                    return true;
                }
            } else {
                return true;
            }
        }

        return false;
	}

	array<EntityAI> GetPlayerItems() {
        array<EntityAI> itemsArray = new array<EntityAI>;
        GetInventory().EnumerateInventory(InventoryTraversalType.INORDER, itemsArray);

        return itemsArray;
    }
}