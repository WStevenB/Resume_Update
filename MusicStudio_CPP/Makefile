CC = g++

OBJ_DIR := obj
BIN_DIR := bin

subsystem:
	$(MAKE) -C FrequencyDetector
	$(MAKE) -C SheetMusicStudio
	$(MAKE) -C TrackRecorder
	$(MAKE) -C SongFinalizer
	$(MAKE) -C DualOffset
	$(MAKE) -C MusicXmlWriter

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)