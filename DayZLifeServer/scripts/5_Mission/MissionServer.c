modded class MissionServer {

    private ref DZLEventManager manager;
    private ref Timer paycheckTimer;
    private ref Timer storageTimer;
    private ref DZLCheckController checkController;
    private ref DZLStorageController storageController;

    void MissionServer() {
        paycheckTimer = new Timer;
        storageTimer = new Timer;
    }

    override void OnInit() {
        super.OnInit();

        manager = new DZLEventManager;
        checkController = new DZLCheckController;
        storageController = new DZLStorageController;

        paycheckTimer.Run(60, checkController, "Check", null, true);
        storageTimer.Run(60, storageController, "Check", null, true);

        DZLConfig.Get();
        DZLBuilderManager.Get().Create();
    }

    override PlayerBase OnClientNewEvent(PlayerIdentity identity, vector pos, ParamsReadContext ctx) {
        DZLPlayer dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(identity.GetId());
        if(dzlPlayer.WillHealByMedic() || dzlPlayer.WillHealByHospital()) {
            DZLStoreItem playerData = dzlPlayer.GetPlayerData();

            string type = "SurvivorF_Judy";
            if(playerData) {
                pos = playerData.positionOfStore;
                type = playerData.type;
            }

            if(dzlPlayer.WillHealByHospital()) {
                pos = TBRReviveConfig.Get().hospitalSpawnPoints.GetRandomElement().point;
            }

            CreateCharacter(identity, pos, ctx, type);

            if(playerData) {
                array<ref DZLStoreItem> items = playerData.GetAttached();
                foreach(DZLStoreItem item: items) {
                    DZLSpawnHelper.Add(m_player, item);
                }
            }
            float factorShock = 1.0;
            float factorBlood = 1.0;
            float factorHealth = 1.0;
            if(dzlPlayer.WillHealByMedic()) {
                factorHealth = 0.05;
                factorBlood = 0.6;
                factorShock = 0;
                array<string> damageZone = new array<string>;

                damageZone.Insert("RightFoot");
                damageZone.Insert("LeftFoot");
                damageZone.Insert("LeftForeArmRoll");
                damageZone.Insert("RightForeArmRoll");
                damageZone.Insert("Head");

                int randCut = Math.RandomIntInclusive(2, 6);

                for(int x = 0; x < randCut; x++) {
                    string damageZ = damageZone.GetRandomElement();
                    m_player.GetBleedingManagerServer().AttemptAddBleedingSourceBySelection(damageZ);
                    factorBlood += 0.1;
                }
            }

            m_player.SetHealth01("GlobalHealth", "Health", factorHealth);
            m_player.SetHealth01("GlobalHealth", "Shock", factorShock);
            m_player.SetHealth01("GlobalHealth", "Blood", factorBlood);
        } else {
            super.OnClientNewEvent(identity, pos, ctx);
            GetGame().RPCSingleParam(null, DZL_RPC.NEW_SPAWN_CLIENT, null, true, identity);
        }

        dzlPlayer.ResetDeadState();
#ifdef TBRevivePlayerClient
        TBREmergencies.Get().Remove(identity.GetId());
#endif

        return m_player;
    }
}
