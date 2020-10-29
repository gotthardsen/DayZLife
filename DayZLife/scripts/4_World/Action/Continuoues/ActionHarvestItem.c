class ActionHarvestItemCB : ActionContinuousBaseCB
{
	override void CreateActionComponent() {}
}

class ActionHarvestItem: ActionContinuousBase
{
    ref DZLJobConfig config;
    bool done = false;

    DZLJobConfig GetConfig() {
        if (!config) {
            config = new DZLJobConfig;
        }

        return config;
    }

	void ActionHarvestItem() {
		m_CallbackClass = ActionHarvestItemCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_RESTRAINTARGET;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		done = false;
	}

	override void Start(ActionData action_data) {
		GetConfig();
		vector playerPosition = action_data.m_Player.GetPosition();
		
		DZLWorkZone zone = FindZone(playerPosition, config);
		if (zone) {
			action_data.m_ActionComponent = new CAContinuousTime(zone.timeToHarvestPerItemInSeconds);
		}

		super.Start(action_data);
	}

	override void CreateConditionComponents() {
		m_ConditionTarget = new CCTNone;
		m_ConditionItem = new CCINonRuined;
		done = false;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item )
	{
		EntityAI item_in_hands_source = player.GetHumanInventory().GetEntityInHands();
		if(!item_in_hands_source) return false;

		string handItemType = item_in_hands_source.GetType();

		if(GetGame().IsServer()) {
			config = GetConfig();
		} else if(player && player.config) {
		    config = player.config.jobConfig;
		}

		DebugMessageDZL("has config ????");
		if (!config) return false;
		DebugMessageDZL("has config");
		
		
		vector playerPosition = player.GetPosition();
		
		DZLWorkZone zone = FindZone(playerPosition, config);
		if (zone) {
			DebugMessageDZL("has zone");
			foreach(DZLHarvestItemToolRelation relation: zone.harvestItemToolRelation) {
			    DebugMessageDZL("check relation");
                foreach(string _item: relation.itemsThatNeededForHarvest) {
                    DebugMessageDZL("check item "+ handItemType + " " + _item);
                    if (handItemType.ToLower() == _item.ToLower()) {
						if (GetGame().IsServer() && 0 == item_in_hands_source.GetHealth()) {
							DebugMessageDZL("not item health");
                            return false;
                        } 
						DebugMessageDZL("all good");
                        return true;
                    }
				}
			}
		} else {
			DebugMessageDZL("no zone");
		}

		return false;
	}

	override string GetText(){
		return "#start_work";
	}
	
	override void OnUpdate(ActionData action_data) {
		super.OnUpdate(action_data);
		if (action_data.m_State == UA_FINISHED && done == false) {
			done = true;

			EntityAI item_in_hands_source = action_data.m_Player.GetHumanInventory().GetEntityInHands();
            if(!item_in_hands_source) return;

            string handItemType = item_in_hands_source.GetType();
			
			DZLWorkZone zone = FindZone(action_data.m_Player.GetPosition(), GetConfig());

			if (zone) {
			    array<DZLHarvestItemToolRelation> matchedRelations = new array<DZLHarvestItemToolRelation>;

			    foreach(DZLHarvestItemToolRelation relation: zone.harvestItemToolRelation) {
                    foreach(string _item: relation.itemsThatNeededForHarvest) {
                        if (handItemType == _item) {
                            if (0 == item_in_hands_source.GetHealth()) {
                                matchedRelations.Insert(relation);
                            }
                        }
                    }
                }

				if (matchedRelations.Count() == 0) return;
				
				DZLHarvestItemToolRelation randRelation = matchedRelations.GetRandomElement();
				
				if (!randRelation) return;
				
				string randomItemType = randRelation.itemsThatCanHarvest.GetRandomElement();

                InventoryLocation inventoryLocation = new InventoryLocation;

                EntityAI item;
				if (action_data.m_Player.GetInventory().FindFirstFreeLocationForNewEntity(randomItemType, FindInventoryLocationType.ANY, inventoryLocation)) {
                    item = action_data.m_Player.GetHumanInventory().CreateInInventory(randomItemType);
                } else if (!action_data.m_Player.GetHumanInventory().GetEntityInHands()) {
                    item = action_data.m_Player.GetHumanInventory().CreateInHands(randomItemType);
                }

                if (!item) {
                    GetGame().RPCSingleParam(action_data.m_Player, ERPCs.RPC_USER_ACTION_MESSAGE, new Param1<string>("#no_space_left_in_inventory"), true, action_data.m_Player.GetIdentity());
                }

				item_in_hands_source.SetHealth(item_in_hands_source.GetHealth() - zone.damagePerHarvestItem);
			}
		    
		} else if ((action_data.m_State == UA_CANCEL || action_data.m_State == UA_INTERRUPT || action_data.m_State == UA_FAILED) && done == false) {
		    done = true;
		}
	}

	override void OnStartServer(ActionData action_data) {
	    done = false;
	}


	private DZLWorkZone FindZone(vector playerPosition, DZLJobConfig config) {
	    if (!playerPosition) {
			DebugMessageDZL("No player pos");
            return null;
        }

	    foreach(DZLWorkZone zone: config.workZones) {
            if(vector.Distance(zone.position, playerPosition) <= zone.range) {
				DebugMessageDZL("is in range");
                return zone;
            }
        }
        return null;
    }

};
