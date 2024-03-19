modded class PlayerBase {
    private ref DZLLicenceMenu licenceMenu;
    private ref DZLLicenceProgressBar progressBarLicence;
    private ref DZLCarRaidProgressBar progressBarRaidCar;
    private ref DZLHarvestProgressBar progressBarHarvest;
    private ref DZLMessageMenu messageMenu;
    private ref DZLPlayerMoneyTransferMenu moneyTransferMenu;
    private ref DZLSpawnPositionMenu spawnPositionMenu;
    private ref DZLLoadOutMenu loadOutMenu;
    private ref DZLPlayerArrestMenu arrestMenu;
    private ref DZLPlayerTicketMenu ticketMenu;
    private ref DZLPlayerPayTicketMenu payTicketMenu;
    private ref DZLCarMenu carMenu;
    private ref DZLCarStorageMenu carStorageMenu;
    private ref DZLMedicHelpMenu healMenu;
    private ref DZLMessageSystemMenu messageSystemMenu;
    private ref DZLBankingMenu bankingMenu;
    private ref DZLTraderMenu traderMenu;
    private ref DZLAlmanacMenu almanacMenu;
    private ref DZLFractionMenu fractionMenu;
    private ref DZLTuningMenu tuningMenu;
    private ref DZLPlayer dzlPlayer;

    bool willHeal = false;
    bool willDie = false;
    int moneyPlayerIsDead = 0;
    bool isOnHarvest = false;
    bool isPolice = false;
    bool medicHelpMenuWasShown = false;
    private bool canRespawn = true;
    private ref Timer enableToHospital;
    bool canHealInHospital = false;
    bool canSeeKillButton = false;
    int waitForHospital = 0;
    int medicCount = 0;

    float deltaTimeLastUpdate = 0;

    private string playerUID;

    override void Init() {
        super.Init();
        RegisterNetSyncVariableInt("moneyPlayerIsDead", 0, 99999999999);
        RegisterNetSyncVariableBool("canRespawn");
    }

    void EnableTimerEnableHospital() {
        enableToHospital = new Timer;
        enableToHospital.Run(1, this, "EnableToHospital", null, true);
        waitForHospital = 0;
    }

    void EnableToHospital() {
        ++waitForHospital;
        if(GetWaitTimeForHospital() < 1) {
            canHealInHospital = true;
        }
        if(GetWaitTimeForKill() < 1) {
            canSeeKillButton = true;
        }

        if(canHealInHospital && canSeeKillButton) {
            enableToHospital.Stop();
        }
    }

    int IsKillButtonOn() {
        return waitForHospital;
    }

    int GetWaitTimeForHospital() {
        DZLConfig config = DZLConfig.Get();
        if(medicCount >= config.medicConfig.minMedicCountForHospitalTimer) {
            return config.medicConfig.minTimeBeforeHospital - waitForHospital;
        }
        return config.medicConfig.minTimeBeforeHospitalWhenMinMedicNotOnline - waitForHospital;
    }

    int GetWaitTimeForKill() {
        return DZLConfig.Get().medicConfig.minTimeBeforeKillButton - waitForHospital;
    }

    bool CanReSpawn() {
        return !canRespawn && 0 == dzlPlayer.arrestTimeInMinutes;
    }

    string GetPlayerId() {
        if(!playerUID) {
            playerUID = GetIdentity().GetId();
        }

        return playerUID;
    }

    bool IsDZLPlayer() {
        return !!GetIdentity();
    }

    override void SetActions(out TInputActionMap InputActionMap) {
        super.SetActions(InputActionMap);

        AddAction(DZLActionRobMoney, InputActionMap);
        AddAction(DZLActionRobMoneyFromDead, InputActionMap);
        AddAction(DZLActionHarvestItem, InputActionMap);
        AddAction(DZLActionTransferMoney, InputActionMap);
        AddAction(DZLActionOpenArrestMenu, InputActionMap);
        AddAction(DZLActionOpenTicketMenu, InputActionMap);
        AddAction(DZLActionGiveNumber, InputActionMap);
    }

    override void CheckDeath() {
        if(IsPlayerSelected() && !IsAlive()) {
            if(!medicHelpMenuWasShown) {
                ShowHealMenu();
                EnableTimerEnableHospital();
                PPEffects.SetUnconsciousnessVignette(1000);
            } else if(willDie) {
                SimulateDeath(true);
                m_DeathCheckTimer.Stop();
            }
        }
    }

    void RequestUpdateDZLPlayer() {
        GetGame().RPCSingleParam(this, DZL_RPC.PLAYER_DATA, null, true);
        GetGame().RPCSingleParam(this, DZL_RPC.PLAYER_BANK_DATA, null, true);
    }

    void DisplayMessage(string message) {
        GetMessageMenu();
        messageMenu.SetText(message);
        messageMenu.Init();
        messageMenu.Show();
    }

    void UpdatePlayerAtDependencies() {
        dzlPlayer = DZLPlayerClientDB.Get().GetDZLPlayer();
        dzlPlayer.player = this;
        if(bankingMenu && bankingMenu.IsVisible()) {
            bankingMenu.UpdatePlayer(this);
        } else if(traderMenu && traderMenu.IsVisible()) {
            traderMenu.UpdatePlayer(this);
        } else if(licenceMenu && licenceMenu.IsVisible()) {
            licenceMenu.UpdatePlayer(this);
        } else if(progressBarLicence && progressBarLicence.IsVisible()) {
            progressBarLicence.UpdatePlayer(this);
        } else if(loadOutMenu && loadOutMenu.IsVisible()) {
            loadOutMenu.UpdatePlayer(this);
        } else if(arrestMenu && arrestMenu.IsVisible()) {
            arrestMenu.UpdatePlayer(this);
        } else if(ticketMenu && ticketMenu.IsVisible()) {
            ticketMenu.UpdatePlayer(this);
        } else if(payTicketMenu && payTicketMenu.IsVisible()) {
            payTicketMenu.UpdatePlayer(this);
        } else if(carMenu && carMenu.IsVisible()) {
            carMenu.UpdatePlayer(this);
        } else if(carStorageMenu && carStorageMenu.IsVisible()) {
            carStorageMenu.UpdatePlayer(this);
        } else if(healMenu && healMenu.IsVisible()) {
            healMenu.UpdatePlayer(this);
        } else if(messageSystemMenu && messageSystemMenu.IsVisible()) {
            messageSystemMenu.UpdatePlayer(this);
        }
    }

    DZLCarMenu GetCarMenu(CarScript car) {
        carMenu = new DZLCarMenu;
        InitMenu(carMenu);
        carMenu.SetCar(car);

        return carMenu;
    }

    DZLMedicHelpMenu GetMedicHealMenu() {
        healMenu = new DZLMedicHelpMenu;
        InitMenu(healMenu);

        return healMenu;
    }

    DZLCarStorageMenu GetCarStorageMenu() {
        carStorageMenu = new DZLCarStorageMenu;
        InitMenu(carStorageMenu);

        return carStorageMenu;
    }

    private void InitMenu(DZLBaseMenu menu) {
        menu.SetPlayer(this);
    }

    DZLMessageMenu GetMessageMenu() {
        messageMenu = new DZLMessageMenu();
        return messageMenu;
    }

    DZLAlmanacMenu GetAlmanacMenu() {
        almanacMenu = new DZLAlmanacMenu();
        InitMenu(almanacMenu);
        return almanacMenu;
    }

    DZLFractionMenu GetFractionMenu() {
        fractionMenu = new DZLFractionMenu();
        InitMenu(fractionMenu);
        return fractionMenu;
    }

    DZLTraderMenu GetTraderMenu(DZLTraderPosition position) {
        traderMenu = new DZLTraderMenu(position);
        InitMenu(traderMenu);
        return traderMenu;
    }

    DZLBankingMenu GetBankingMenu() {
        bankingMenu = new DZLBankingMenu();
        InitMenu(bankingMenu);
        return bankingMenu;
    }

    DZLLicenceMenu GetLicenceMenu() {
        licenceMenu = new DZLLicenceMenu();
        InitMenu(licenceMenu);
        return licenceMenu;
    }

    DZLLoadOutMenu GetLoadOutMenu() {
        loadOutMenu = new DZLLoadOutMenu();
        InitMenu(loadOutMenu);
        return loadOutMenu;
    }

    DZLPlayerArrestMenu GetArrestMenu() {
        arrestMenu = new DZLPlayerArrestMenu();
        InitMenu(arrestMenu);
        return arrestMenu;
    }

    DZLPlayerTicketMenu GetTicketMenu() {
        ticketMenu = new DZLPlayerTicketMenu();
        InitMenu(ticketMenu);
        return ticketMenu;
    }

    DZLPlayerPayTicketMenu GetPayTicketMenu() {
        payTicketMenu = new DZLPlayerPayTicketMenu();
        InitMenu(payTicketMenu);
        return payTicketMenu;
    }

    DZLPlayerMoneyTransferMenu GetPlayerMoneyTransferMenu() {
        moneyTransferMenu = new DZLPlayerMoneyTransferMenu();
        InitMenu(moneyTransferMenu);
        return moneyTransferMenu;
    }

    DZLLicenceProgressBar GetLicenceProgressBar() {
        progressBarLicence = new DZLLicenceProgressBar();
        progressBarLicence.SetPlayer(this);
        return progressBarLicence;
    }

    DZLHarvestProgressBar GetHarvestProgressBar() {
        progressBarHarvest = new DZLHarvestProgressBar();
        progressBarHarvest.SetPlayer(this);
        return progressBarHarvest;
    }

    DZLCarRaidProgressBar GetRaidCarProgressBar() {
        progressBarRaidCar = new DZLCarRaidProgressBar();
        progressBarRaidCar.SetPlayer(this);
        return progressBarRaidCar;
    }

    DZLSpawnPositionMenu GetSpawnPositionMenu() {
        spawnPositionMenu = new DZLSpawnPositionMenu();
        InitMenu(spawnPositionMenu);
        return spawnPositionMenu;
    }

    DZLMessageSystemMenu GetMessageSystemMenu() {
        messageSystemMenu = new DZLMessageSystemMenu();
        InitMenu(messageSystemMenu);
        return messageSystemMenu;
    }

    DZLTuningMenu GetTuningMenu() {
        tuningMenu = new DZLTuningMenu();
        InitMenu(tuningMenu);
        return tuningMenu;
    }

    void RefreshMessageSystem() {
        if(messageSystemMenu) messageSystemMenu.RefreshMessageSystem();
    }

    float GetMoneyPlayerIsDead() {
        return moneyPlayerIsDead;
    }

    void SetMoneyPlayerIsDead(float money) {
        moneyPlayerIsDead = money;
        money = 0;
    }

    DZLCraftLicence GetLicenceByPosition() {
        if(!GetDZLPlayer() || !DZLConfig.Get() || !DZLConfig.Get().licenceConfig) return null;

        vector playerPosition = GetPosition();
        if(!playerPosition) {
            return null;
        }

        foreach(string licenceId: GetDZLPlayer().licenceIds) {
            DZLCraftLicence licence = DZLConfig.Get().licenceConfig.licenceCollection.FindById(licenceId);

            if(!licence) continue;

            if(vector.Distance(licence.position, playerPosition) <= 3) {
                return licence;
            }
        }
        if(GetGame().IsServer()) {
            DZLSendMessage(GetIdentity(), "#you_have_not_the_dependency_licence");
        }
        return null;
    }

    DZLTraderPosition GetTraderByPosition(int distance = 3) {
        vector playerPosition = GetPosition();
        if(!playerPosition || !DZLConfig.Get() || !DZLConfig.Get().traderConfig) {
            return null;
        }

        array<ref DZLTraderPosition> positions = DZLConfig.Get().traderConfig.positions.positions;

        foreach(DZLTraderPosition position: positions) {
            float distanceToPos = vector.Distance(position.position, playerPosition);
            if(distanceToPos <= distance) {
                return position;
            }
        }

        return null;
    }

    DZLTunerPosition GetTunerPositionByPosition(int distance = 3) {
        vector playerPosition = GetPosition();
        if(!playerPosition || !DZLConfig.Get() || !DZLConfig.Get().tuningConfig) {
            return null;
        }

        array<ref DZLTunerPosition> positions = DZLConfig.Get().tuningConfig.tuner;

        foreach(DZLTunerPosition position: positions) {
            float distanceToPos = vector.Distance(position.position, playerPosition);
            if(distanceToPos <= distance) {
                return position;
            }
        }

        return null;
    }

    array<EntityAI> GetPlayerItems() {
        array<EntityAI> itemsArray = new array<EntityAI>;
        GetInventory().EnumerateInventory(InventoryTraversalType.INORDER, itemsArray);

        return itemsArray;
    }

    bool HasInInventory(string type) {
        array<EntityAI> items = GetPlayerItems();
        foreach(EntityAI item: items) {
            if(item.GetType() == type) {
                return true;
            }
        }
        return false;
    }

    array<EntityAI> GetItemsByTypeFromInventory(string type) {
        array<EntityAI> items = GetPlayerItems();
        array<EntityAI> itemsFound = new array<EntityAI>;
        foreach(EntityAI item: items) {
            if(item.GetType() == type) {
                itemsFound.Insert(item);
            }
        }
        return itemsFound;
    }

    override void RemoveAllItems() {
        array<EntityAI> itemsArray = new array<EntityAI>;
        ItemBase item;
        GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);

        for(int i = 0; i < itemsArray.Count(); i++) {
            Class.CastTo(item, itemsArray.Get(i));
            if(item && !item.IsInherited(SurvivorBase)) {
                GetGame().ObjectDelete(item);
            }
        }
    }

    void ShowHealMenu() {
        if(GetGame().IsClient()) {
            if(!healMenu && medicHelpMenuWasShown == false) {
                if(g_Game.GetUIManager().GetMenu()) {
                    g_Game.GetUIManager().GetMenu().Close();
                }
                DZLConfig config = DZLConfig.Get();
                if(config && config.medicConfig && medicHelpMenuWasShown == false) {
                    GetGame().GetUIManager().ShowScriptedMenu(GetMedicHealMenu(), NULL);
                    medicHelpMenuWasShown = true;
                }
            }
        }
    }

    void ShowHealMenuFromMission() {
        if(GetGame().IsClient() && medicHelpMenuWasShown) {
            medicHelpMenuWasShown = false;
            ShowHealMenu();
        }
    }

    DZLPlayer GetDZLPlayer() {
        if(dzlPlayer) return dzlPlayer;

        dzlPlayer = DZLPlayerClientDB.Get().GetDZLPlayer();
        if(dzlPlayer) dzlPlayer.player = this;

        return dzlPlayer;
    }

    DZLBank GetBank() {
        return DZLPlayerClientDB.Get().GetBank();
    }

    bool CanOpenMessageMenu() {
        if(IsRestrained()) return false;
        if(IsUnconscious()) return false;
        if(!DZLConfig.Get()) return false;
        if(!DZLConfig.Get().messageConfig) return false;

        if(!DZLConfig.Get().messageConfig.mustHavePersonalRadio) return true;

        array<EntityAI> radios = GetItemsByTypeFromInventory("PersonalRadio");

        if(radios.Count() < 1) return false;

        if(!DZLConfig.Get().messageConfig.radioMustHaveBattery) return true;

        foreach(EntityAI radio: radios) {
            if(radio.GetInventory()) {
                for(int i = 0; i < radio.GetInventory().AttachmentCount(); i++) {
                    EntityAI attachment = radio.GetInventory().GetAttachmentFromIndex(i);
                    if(attachment && attachment.GetType() == "Battery9V") {
                        Battery9V itemCast = Battery9V.Cast(attachment);



                        if(itemCast && itemCast.GetQuantity() > 0) {
                            float energy = itemCast.GetCompEM().GetEnergy();

                            if(energy > 0) return true;
                        }
                    }
                }
            }
        }

        return false;
    }

}
