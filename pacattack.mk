##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=pacattack
ConfigurationName      :=Debug
WorkspacePath          := "C:\Development\Projects\git\pacattack"
ProjectPath            := "C:\Development\Projects\git\pacattack"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Fueler
Date                   :=3/11/2013
CodeLitePath           :="C:\Program Files (x86)\CodeLite"
LinkerName             :=gcc
SharedObjectLinkerName :=gcc -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-g 
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
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=windres
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)deps/SDL-1.2.15/include $(IncludeSwitch)deps/SDL-1.2.15/include/SDL $(IncludeSwitch)deps/SDL_image-1.2.12/include $(IncludeSwitch)deps/SDL_ttf-2.0.11/include $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)stdc++ $(LibrarySwitch)mingw32 $(LibrarySwitch)SDLmain $(LibrarySwitch)SDL $(LibrarySwitch)SDL_image $(LibrarySwitch)SDL_ttf 
ArLibs                 :=  "stdc++" "mingw32" "SDLmain" "SDL" "SDL_image" "SDL_ttf" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)deps/SDL-1.2.15/lib $(LibraryPathSwitch)deps/SDL_image-1.2.12/lib/x86 $(LibraryPathSwitch)deps/SDL_ttf-2.0.11/lib/x86 

##
## Common variables
## AR, CXX, CC, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := gcc
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files (x86)\CodeLite
WXWIN:=C:\Development\Libraries\wxWidgets
PATH:=$(WXWIN)\lib\gcc_dll;$(PATH)
WXCFG:=gcc_dll\mswu
UNIT_TEST_PP_SRC_DIR:=C:\Development\Utilities\UnitTestC++
Objects0=$(IntermediateDirectory)/log$(ObjectSuffix) $(IntermediateDirectory)/ewatce$(ObjectSuffix) $(IntermediateDirectory)/game$(ObjectSuffix) $(IntermediateDirectory)/main$(ObjectSuffix) 

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
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/log$(ObjectSuffix): log.cpp $(IntermediateDirectory)/log$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Development/Projects/git/pacattack/log.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/log$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/log$(DependSuffix): log.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/log$(ObjectSuffix) -MF$(IntermediateDirectory)/log$(DependSuffix) -MM "log.cpp"

$(IntermediateDirectory)/log$(PreprocessSuffix): log.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/log$(PreprocessSuffix) "log.cpp"

$(IntermediateDirectory)/ewatce$(ObjectSuffix): ewatce.cpp $(IntermediateDirectory)/ewatce$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Development/Projects/git/pacattack/ewatce.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ewatce$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ewatce$(DependSuffix): ewatce.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ewatce$(ObjectSuffix) -MF$(IntermediateDirectory)/ewatce$(DependSuffix) -MM "ewatce.cpp"

$(IntermediateDirectory)/ewatce$(PreprocessSuffix): ewatce.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ewatce$(PreprocessSuffix) "ewatce.cpp"

$(IntermediateDirectory)/game$(ObjectSuffix): game.cpp $(IntermediateDirectory)/game$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Development/Projects/git/pacattack/game.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/game$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/game$(DependSuffix): game.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/game$(ObjectSuffix) -MF$(IntermediateDirectory)/game$(DependSuffix) -MM "game.cpp"

$(IntermediateDirectory)/game$(PreprocessSuffix): game.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/game$(PreprocessSuffix) "game.cpp"

$(IntermediateDirectory)/main$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Development/Projects/git/pacattack/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main$(PreprocessSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main$(PreprocessSuffix) "main.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/log$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/log$(DependSuffix)
	$(RM) $(IntermediateDirectory)/log$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/ewatce$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ewatce$(DependSuffix)
	$(RM) $(IntermediateDirectory)/ewatce$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/game$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/game$(DependSuffix)
	$(RM) $(IntermediateDirectory)/game$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile).exe
	$(RM) ".build-debug/pacattack"


