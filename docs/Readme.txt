10-12-14
Software Test Plan 
1.0
Table of contents
Test Plan Identifier
Specify the unique identifier assigned to this test plan.
Test Items
Identify the test items including their version/revision level. Also specify characteristics of their transmittal media that impact hardware requirements or indicate the need for logical or physical transformations before testing can begin (e.g., programs must be transferred from tape to disk).
Features to be Tested
Identify all software features and combinations of software features to be tested. Identify the test design specification associated with each feature and each combination of features.
Features Not to be Tested 
Identify all features and significant combinations of features that are in the requirements document that will not be tested and the reasons.
Approach
Describe the overall approach to testing:  extent of verification of requirements, use of test methods, use of test input files, simulated versus actual use scenarios, differences between test environment and actual use environment.
Item Pass/Fail Criteria (optional based on risk level)
Specify the criteria to be used to determine whether each feature has passed or failed testing.
Test Deliverables (optional based on risk level)
Minimum deliverables:
* This document
* Actual test results
Procedure Steps (optional based on risk level)
The steps required to perform the testing.  Typically documents in a checklist.  See the attached table below as one example.
Test Log
Provide an entry for each test run including the version of the software tested, date, tester, associated files used or generated.
Test Summary
Summary of results with references to any unresolved problem reports.




Software Title: Turing Machine Application
Version 2.0
SYSTEM PREREQUISITES:
* A linux operating system 
* a gcc compiler
INSTALLATION NOTES:
To install the TMA you will need a Turing Machine Definition File and an Input String File in your applications directory. Also, the correct way to run the TMA, for example, is to type "./tm tmDef", where tmDef is the name of the Turing Machine Definition File that is in the directory from where the TMA is being executed.
BUG FIXES
The bugs fixed with respect to this document are listed here. The tabs include fields directly specified in BugZilla. RD signifies Requirement Document and DD is a reference to Design Document. The Severity of Defect are direct enumerators defined in BugZilla as is the Unique Defect Identifier. 
Unique Defect IdentifierSeverity of DefectLocation of Defect System Configuration when Defect FoundStatusTypeArea of ImpactWho Found DefectResponisble for Fixing Defect3ResolvedP1CriticalRDInput String FileMichael DeganCody Curry2.028ResolvedP1EnhancementRDDelete Command/Run CommandDaniel MartinezDaniel Martinez2.023ResolvedP3MinorRDInput/Tape AlphabetCody CurryCody Curry2.019ResolvedP5EnhancementRDReserved CharactersChristopher WilkinsChristoper Wilkins2.020ResolvedP5EnhancementRDInstantaneous DescriptionChristopher WilkinsChristoper Wilkins2.033ResolvedP5EnhancementRDAll DocumentsChristopher WilkinsChristoper Wilkins2.032ResolvedP5EnhancementRDAll DocumentsMichael DeganCody Curry2.027ResolvedP5CriticalDDInput String ObjectChristopher WilkinsMichael Degan2.0

KNOWN ISSUES (that will be addressed in a future release)
The bugs specified below will be fixed on the next iteration of corrections. The tabs include fields directly specified in BugZilla. RD signifies Requirement Document and DD is a reference to Design Document. The Severity of Defect are direct enumerators defined in BugZilla as is the Unique Defect Identifier.
Unique Defect IdentifierSeverity of DefectLocation of Defect System Configuration when Defect FoundStatusTypeArea of ImpactWho Found DefectResponisble for Fixing Defect14NewP2NormalDDInsert CommandDaniel MartinezDaniel Martinez2.115NewP2NormalDDExit CommandDaniel MartinezMichael Degan2.134NewP5EnhancementRDRD and DDMichael DeganDaniel Martinez2.122NewP5MajorRDRD and DDChristopher WilkinsMichael Degan2.126NewP5MajorRDInput String FileChristopher WilkinsMichael Degan2.129NewP5MajorDDTransition MethodDaniel MartinezMichael Degan2.130NewP5TrivialDDTruncate CommandCody CurryMichael Degan2.131NewP5EnhancementRDRun CommandMichael DeganMichael Degan2.145NewP5MajorRDDelete CommandMichael DeganMichael Degan2.146NewP5CriticalRDTruncate CommandMichael DeganMichael Degan2.151NewP5CriticalRDSet CommandMichael DeganMichael Degan2.1
