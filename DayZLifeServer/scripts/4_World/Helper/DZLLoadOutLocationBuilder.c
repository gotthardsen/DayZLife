class DZLLoadOutLocationBuilder: DZLLicenceLocationBuilder {

    override static void Create() {
		array<ref DZLLoadOutPosition> positions = DZLConfig.Get().jobConfig.loadOutsCops.loadOutPosition;
		
		foreach(DZLLoadOutPosition position: positions) {
           PlayerBase trader = DZLLoadOutLocationBuilder.CreatePositions(position, false, false, false, true);
        }
	}
};
