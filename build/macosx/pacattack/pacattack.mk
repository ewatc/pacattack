##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=pacattack
ConfigurationName      :=Debug
WorkspacePath          := "/Users/waynemoorefield/Documents/development/pacattack/build/macosx/pacattack"
ProjectPath            := "/Users/waynemoorefield/Documents/development/pacattack/build/macosx/pacattack"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Wayne Moorefield
Date                   :=2013-05-11
CodeLitePath           :="/Users/waynemoorefield/Library/Application Support/codelite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -dynamiclib -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="pacattack.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -framework SDL -framework Cocoa -framework SDL_ttf
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)/Library/Frameworks/SDL.framework/Headers $(IncludeSwitch)/Library/Frameworks/SDL_ttf.framework/Headers 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/Library/Frameworks/SDL.framework $(LibraryPathSwitch)/Library/Frameworks/SDL_ttf.framework 

##
## Common variables
## AR, CXX, CC, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)


##
## User defined environment variables
##
CodeLiteDir:=/Applications/codelite.app/Contents/SharedSupport/
Objects0=$(IntermediateDirectory)/SDLMain$(ObjectSuffix) $(IntermediateDirectory)/pacattack_ewatce$(ObjectSuffix) $(IntermediateDirectory)/pacattack_game$(ObjectSuffix) $(IntermediateDirectory)/pacattack_log$(ObjectSuffix) $(IntermediateDirectory)/pacattack_main$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/SDLMain$(ObjectSuffix): SDLMain.m $(IntermediateDirectory)/SDLMain$(DependSuffix)
	$(CXX) $(IncludePCH) -x objective-c $(SourceSwitch) "/Users/waynemoorefield/Documents/development/pacattack/build/macosx/pacattack/SDLMain.m" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SDLMain$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SDLMain$(DependSuffix): SDLMain.m
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SDLMain$(ObjectSuffix) -MF$(IntermediateDirectory)/SDLMain$(DependSuffix) -MM "SDLMain.m"

$(IntermediateDirectory)/SDLMain$(PreprocessSuffix): SDLMain.m
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SDLMain$(PreprocessSuffix) "SDLMain.m"

$(IntermediateDirectory)/pacattack_ewatce$(ObjectSuffix): ../../../ewatce.cpp $(IntermediateDirectory)/pacattack_ewatce$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/waynemoorefield/Documents/development/pacattack/ewatce.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/pacattack_ewatce$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pacattack_ewatce$(DependSuffix): ../../../ewatce.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pacattack_ewatce$(ObjectSuffix) -MF$(IntermediateDirectory)/pacattack_ewatce$(DependSuffix) -MM "../../../ewatce.cpp"

$(IntermediateDirectory)/pacattack_ewatce$(PreprocessSuffix): ../../../ewatce.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pacattack_ewatce$(PreprocessSuffix) "../../../ewatce.cpp"

$(IntermediateDirectory)/pacattack_game$(ObjectSuffix): ../../../game.cpp $(IntermediateDirectory)/pacattack_game$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/waynemoorefield/Documents/development/pacattack/game.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/pacattack_game$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pacattack_game$(DependSuffix): ../../../game.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pacattack_game$(ObjectSuffix) -MF$(IntermediateDirectory)/pacattack_game$(DependSuffix) -MM "../../../game.cpp"

$(IntermediateDirectory)/pacattack_game$(PreprocessSuffix): ../../../game.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pacattack_game$(PreprocessSuffix) "../../../game.cpp"

$(IntermediateDirectory)/pacattack_log$(ObjectSuffix): ../../../log.cpp $(IntermediateDirectory)/pacattack_log$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/waynemoorefield/Documents/development/pacattack/log.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/pacattack_log$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pacattack_log$(DependSuffix): ../../../log.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pacattack_log$(ObjectSuffix) -MF$(IntermediateDirectory)/pacattack_log$(DependSuffix) -MM "../../../log.cpp"

$(IntermediateDirectory)/pacattack_log$(PreprocessSuffix): ../../../log.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pacattack_log$(PreprocessSuffix) "../../../log.cpp"

$(IntermediateDirectory)/pacattack_main$(ObjectSuffix): ../../../main.cpp $(IntermediateDirectory)/pacattack_main$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/waynemoorefield/Documents/development/pacattack/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/pacattack_main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pacattack_main$(DependSuffix): ../../../main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pacattack_main$(ObjectSuffix) -MF$(IntermediateDirectory)/pacattack_main$(DependSuffix) -MM "../../../main.cpp"

$(IntermediateDirectory)/pacattack_main$(PreprocessSuffix): ../../../main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pacattack_main$(PreprocessSuffix) "../../../main.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/SDLMain$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/SDLMain$(DependSuffix)
	$(RM) $(IntermediateDirectory)/SDLMain$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pacattack_ewatce$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pacattack_ewatce$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pacattack_ewatce$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pacattack_game$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pacattack_game$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pacattack_game$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pacattack_log$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pacattack_log$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pacattack_log$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pacattack_main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pacattack_main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pacattack_main$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) ".build-debug/pacattack"


