#!/usr/bin/perl
use Net::Ping;
use Sys::Hostname;
use Socket;
my $bRoot = 0;

my $variableFileName = ".variable";
my $gpsconfFileName  = ".gpsconf";
my $scriptFileName   = "viewCatcher";
my $viewCopySuffix   = "vc";
my $csvFileSuffix = "csv";
my $csvItemSeparator = ",";
my $resultFileSuffix = "tdr";
my $resultOKFlag     = "OK";
my $resultNGFlag     = "NG";

my $txtFileSuffix = "txt";
my $testResultFileName = "AutoTestResult";
my $testNGResultFileName = "AutoTestResult_NG";

my $keyPclPath  = "PclPath";
my $keyJobName  = "JobName";
my $keySend     = "Send";
my $keyPatch    = "Patch";
my $keySet      = "Set";
my $keyCheck    = "Check";
my $keyMd5sum   = "Md5sum";
my $keyCRC 		= "CRC";
my $isCRC		= 0;
my $isRAS		= 0;
my $ras2pngScript = "ras2png";
my $crcChecklist = "crc.crc";
my $crcChecklist2 = "crc.crc2";
my $keyViewList = "ViewList";

#jobinfo key
my $keyQty  = "jobinfo_qty";
my $keyColorCount  = "jobinfo_color_count";
my $keyOutmode  = "jobinfo_outmode";
my $keyBinding  = "jobinfo_binding";
my $keyFinish  = "jobinfo_finish";
my $keyStaple  = "staple";
my $keyPunch  = "punch";
my $keyFold  = "fold";

my $JobNum      = 0;
my @PageNumList = ();
my %TDDInfoHash = {};
my %LogInfoHash = {};

my %gpsconfHash  = {};
my %variableHash = {};

my $bDebug      = 0;
my $iDebugLevel = 0;
my $bIP         = 0;
my $bLog        = 0;

my $iCheckCount = 0;
my $iNGCount    = 0;

my $sleep       = 10;
#my $ip          = "172.25.79.206";
my $ip;
my $szLogFileName;
my $hLogFile;
my $bLogFile    = 0;

($sec, $min, $hour, $mday, $mon, $year) = (localtime(time))[0..5];
$year += 1900;
$mon += 1;
$sec = sprintf("%02d", $sec);
$min = sprintf("%02d", $min);
$hour = sprintf("%02d", $hour);
$mday = sprintf("%02d", $mday);
$mon = sprintf("%02d", $mon);

main();

sub main {
	print "===== Tdd Start =====\n";

	$host = hostname();
	$ip = inet_ntoa(scalar gethostbyname($host || 'localhost'));
	PrintLog("host : $host, ip : $ip\n");

	open ALLTDDRESULT,   "> $testResultFileName"."_Middle.$txtFileSuffix";
	open ALLTDDNGRESULT,   "> $testNGResultFileName"."_Middle.$txtFileSuffix";

	print "Command: perl $0 @ARGV\n";
	if ( @ARGV == 0 ) {
		foreach $file_name ( `find -name "*.tdd"` ) {
			chomp( $file_name );
			print "----- File: $file_name -----\n";
			InitVar();
			InterpretTDDFile( $file_name );
			RunTest( $file_name );
		}
	}
	else {
		foreach my $arg ( @ARGV ) {
			if ( $bDebug ) {
				if ( $arg =~ /^[0-9]+$/ ) {
					print "Debug Level = $arg\n";
					$iDebugLevel = $arg;
					$bDebug = 0;
					next;
				}
				else {
					$iDebugLevel = 1;
					$bDebug = 0;
				}
			}

			if ( $bLog ) {
				$bLogFile = 1;
				$szLogFileName = $arg;
				$bLog = 0;
				next;
			}

			if ( $bIP ) {
				my $ret = checkIP($arg);

				if($ret == -2){
					print "$arg is Not reachable!\n";
					last;
				}elsif($ret == -1){
					print "Invalid IP:$arg!\n";
					last;
				}else{
					print "$arg is reachable!\n";
					$ip = $arg;
				}
				$bIP = 0;
				next;
			}

			if ( $arg =~ /^(-+)(.*)/ ) {
				my $bInvalidCmd = 0;
				if ( $arg =~ /^--(.*)/ || $arg =~ /^-(.*)/ ) {
					my $cmd = $1;

					if ( $cmd =~ /^help$/i ) {
						print "\nThis is TDD tool. Usage:\n\n";
						print "\tperl tdd.pl [options|option=context] [filenames]\n\n";

						print "Options:\n\n";
						print "\t--debug\t\tPrint debug information.\n";
						print "\t--help \t\tPrint this message.\n";
						print "\t--ip   \t\tSet IP Address for sending job. If not set, it will be \"172.25.79.205\".";
						print "\t--log  \t\tOutput message to log file.\n";

						#TODO

						print "";
						next;
					}
					elsif ( $cmd =~ /^isRAS/i ) {
						$isRAS = 1;
						next;
					}
					elsif ( $cmd =~ /^debug$/i ) {
						$bDebug = 1;
						next;
					}
					elsif ( $cmd =~ /^ip$/i ) {
						$bIP = 1;
						next;
					}
					elsif ( $cmd =~ /^log$/i ) {
						$bLog = 1;
						next;
					}
					else {
						$bInvalidCmd = 1;
					}
				}
				else {
					$bInvalidCmd = 1;
				}

				if ( $bInvalidCmd ) {
					print "Invalid command: $arg!!!\n";
					print "Use 'perl tdd.pl --help' for a complete list of options.\n";
					last;
				}
			}
			else {
				my $file_name = $arg;

				open $hLogFile, "> $szLogFileName";

				PrintLog( "----- File: $file_name -----\n");
				if ( -e $file_name ) {
					InitVar();
					InterpretTDDFile( $file_name );
					RunTest( $file_name );
				}
				else {
					PrintLog( "TDD File \"$file_name\" not exist!\n");
					last;
				}

				close $hLogFile;
			}
		}
	}

	close ALLTDDRESULT;
	close ALLTDDNGRESULT;

	open OUTHEADFILE, "> head.txt";
	print OUTHEADFILE "$year/$mon/$mday  $hour:$min:$sec  ", getlogin(), "\n\n";
	print OUTHEADFILE "total check    :    $iCheckCount\n";
	print OUTHEADFILE "NG check       :    $iNGCount\n", "\n\n";
	close OUTHEADFILE;

	`cat head.txt AutoTestResult_Middle.txt > "$testResultFileName.$txtFileSuffix"`;
	`cat head.txt AutoTestResult_NG_Middle.txt > "$testNGResultFileName.$txtFileSuffix"`;

	`rm head.txt AutoTestResult_Middle.txt AutoTestResult_NG_Middle.txt`;

	print "===== Tdd End =====\n";
}

sub InitVar {
	$JobNum      = 0;
	@PageNumList = ();
	%TDDInfoHash = {};
	%LogInfoHash = {};
}

sub RunTest {
	PrintLog( "Test Start...\n" );

	my ( $resultfile ) = @_;
	my $bError = 0;

	print ALLTDDRESULT "$resultfile\n";
	print ALLTDDNGRESULT "$resultfile\n";

	open TDDRESULT,   "> $resultfile"."_ALL.$resultFileSuffix";
	open TDDNGRESULT, "> $resultfile"."_NG.$resultFileSuffix";

	open CSVRESULT, "> $resultfile"."_ALL.$csvFileSuffix";

	if( -e $crcChecklist ){
		`rm $crcChecklist`;
	}

	my $iJobNo;
	for ( $iJobNo = 1 ; $iJobNo <= $JobNum ; $iJobNo++ ) {
		my $currJobInfo = $TDDInfoHash{"Job$iJobNo"};

		my $pclPath;
		if ( exists $TDDInfoHash{"Job$iJobNo"}{"$keyPclPath"} ) {
			$pclPath = $TDDInfoHash{"Job$iJobNo"}{"$keyPclPath"};
		}
		else {
			$pclPath = $TDDInfoHash{"$keyPclPath"};
		}

		my $sendFile        = $TDDInfoHash{"Job$iJobNo"}{"$keySend"};
		my $pclFile         = $pclPath . "pcl";
		my $gpsconfFile     = $pclPath . $gpsconfFileName;
		my $variableFile    = $pclPath . $variableFileName;
		my $gpsconfFileOrg  = $gpsconfFile . "_org";
		my $variableFileOrg = $variableFile . "_org";

		my $bPCLExist = 1;
		my $bJobExist = 1;

		PrintLog( "+++++ PCL: $pclFile, Job: $sendFile, IP: $ip Start... +++++\n" );

		unless ( -e $pclFile ) {
			$bPCLExist = 0;
			PrintLog( "PCL: \"$pclFile\" not exist!\n" );
		}
		unless ( -e $sendFile ) {
			$bJobExist = 0;
			PrintLog( "Job: \"$sendFile\" not exist!\n" );
		}
		unless ( $bPCLExist && $bJobExist ) {
			PrintLog( "+++++ PCL: $pclFile, Job: $sendFile, IP: $ip End +++++\n" );
			next;
		}
		#if( -e $crcChecklist ){
			#`rm $crcChecklist`;
		#}
		
		if ( -e $gpsconfFileOrg ) {
			`rm $gpsconfFile`;
			`cp $gpsconfFileOrg $gpsconfFile`;
			PrintLog( "Recover the gpsconf File...\n" );
		}
		else {
			`cp $gpsconfFile $gpsconfFileOrg`;
			PrintLog( "Save the gpsconf File...\n" );
		}
		if ( -e $variableFileOrg ) {
			`rm $variableFile`;
			`cp $variableFileOrg $variableFile`;
			PrintLog( "Recover the variable File...\n" );
		}
		else {
			`cp $variableFile $variableFileOrg`;
			PrintLog( "Save the variable File...\n" );
		}

		#create script file to save page view
		my $scriptFile = $pclPath . $scriptFileName;
		open SCRIPTFILE, "> $scriptFile";
		print SCRIPTFILE "#!/bin/csh\ncp \$1 \"\$1.$viewCopySuffix\"\n";
		close SCRIPTFILE;
		`chmod +x $scriptFile`;

		InterpretGpsconfigFile( $gpsconfFile );
		InterpretVariableFile( $variableFile );

		my $JobSetHash = $$currJobInfo{"Hash$keySet"};
		PrintLog( "Set Info:\n" );
		foreach ( keys %$JobSetHash ) {
			my $key   = $_;
			my $value = $$JobSetHash{"$_"};
			PrintLog( "\tSet key = $key, value = $value\n" );

			if ( exists $gpsconfHash{$key} ) {
				PrintLog( "\t$key is in the gpsconf file!\n", $iDebugLevel >= 1 );
				if ( $key eq "environment" ) {
					InterpretVariableFile( $value );
				}
				else {
					$gpsconfHash{$key} = $value;
				}
			}
			elsif ( exists $variableHash{$key} ) {
				PrintLog( "\t$key is in the variable file!\n", $iDebugLevel >= 1 );
				$variableHash{$key} = $value;
			}
			else {
				PrintLog( "\tNo Item \"$key\"!!!\n", $iDebugLevel >= 1 );
				die "Error: No Item \"$key\" in neither \".gpsconf\" nor \".variable\""; #TODO
			}
		}

		unless(exists $$JobSetHash{"output_format"}){
			if($isRAS){
				$gpsconfHash{"output_format"} = 0;
				open SCRIPTFILE, "> $ras2pngScript";
				print SCRIPTFILE "#!/bin/csh\nconvert \$1 \$1:r.png\n";
				close SCRIPTFILE;
				`chmod +x $ras2pngScript`;
			}else{
				$gpsconfHash{"output_format"} = 7;
			}
		}
		if($gpsconfHash{"output_format"} == 7){
			$isCRC = 1;
		}else{
			$isCRC = 0;
		}
		
		#update .gpsconf file to use script
		$gpsconfHash{"viewer"} = "$scriptFile";

		UpdateGpsconfigFile( $gpsconfFile );
		UpdateVariableFile( $variableFile );

		#remove output/*.vc
		my $outputPath = $gpsconfHash{"output"};
		if ( $outputPath =~ /^.\/(.*)/ ) {
			$outputPath = $1;
		}

		#if( $iDebugLevel == 0 ) {
			my $outputFile = $pclPath . $outputPath . "/" . "*.vc";
			`rm $outputFile`;
		#}

		RunSim( $pclFile, $sendFile );

		my $profPath = $gpsconfHash{"prof"};
		if ( $profPath =~ /^.\/(.*)/ ) {
			$profPath = $1;
		}

		InterpretLogFile( $pclPath, $profPath, $iJobNo, $sendFile );
		PrintTDDResult( TDDRESULT, TDDNGRESULT, CSVRESULT, $iJobNo );

		#delete temp file
		`cp $gpsconfFileOrg $gpsconfFile`;
		`rm $gpsconfFileOrg`;
		PrintLog( "Recover the gpsconf File...\n" );
		`cp $variableFileOrg $variableFile`;
		`rm $variableFileOrg`;
		PrintLog( "Recover the variable File...\n" );
		`rm $scriptFile`;

		#remove output/*.vc
		#if( $iDebugLevel == 0 ) {
			foreach ( @{ $LogInfoHash{"$keyViewList"} } ) {
				my $outputFile = $pclPath . $outputPath . "/" . $_;
				`rm $outputFile`;
			}
		#}

		PrintLog( "+++++ PCL: $pclFile, Job: $sendFile, IP: $ip End +++++\n" );
	}

	close TDDRESULT;
	close TDDNGRESULT;
	close CSVRESULT;

	PrintLog( "Total Item: $iCheckCount\n\tResult File: $resultfile"."_ALL.$resultFileSuffix\n" );
	PrintLog( "NG Item: $iNGCount\n\tResult File: $resultfile"."_NG.$resultFileSuffix\n" );
	PrintLog( "CRC Check list File: $crcChecklist\n");
	PrintLog( "Test End\n" );
}

sub RunSim {
	my ( $pcl, $file ) = @_;

	PrintLog( "pcl = $pcl, job = $file\n" );

	PrintLog( "Simulator Start...\n" );

	#pcl log file
	my $pcllogFile = join ".",$file,"log";
	open REFSTDOUT, ">&STDOUT";
	open STDOUT, ">$pcllogFile";

	my $pid = fork;
	die "Cannot fork : $!" unless ( defined $pid );

	if ( $pid ) {

		#parent process $pid > 0

		my $loginname = getlogin();
		my $sim_ID = "";
		while ( $sim_ID == "" ) {
			sleep 3;
			if($bRoot) {
				open IN, "ps aux | grep root | grep 'pcl' | grep -v 'grep' |";
			} else {
			open IN, "ps aux | grep $loginname | grep 'pcl' | grep -v 'grep' |";
			}
			while ( $inline = <IN> ) {
				$inline =~ /(\S+)\s+(\S+)/;
				$sim_ID = $2;
			}
		}

		PrintLog( "Waiting GPS Simulator...\n" );
		sleep $sleep;

		#`simprint $ip $file`;
		PrintLog( "Send Job Start...\n", $iDebugLevel >= 1 );
		`./simprint $ip $file`;
		PrintLog( "Send Job End!\n", $iDebugLevel >= 1 );

		# to make the log complete
		PrintLog( "Waiting GPS log...\n" );
		sleep $sleep;

		#kill pcl
		if ( $sim_ID != "" ) {
		
			PrintLog( "Kill PCL...\n", $iDebugLevel >= 1 );
			`kill $sim_ID`;
		}

		#`kill $pid`;

		PrintLog( "Recycle Chirdren...\n", $iDebugLevel >= 1 );
		waitpid( $pid, 0 );

		open STDOUT, ">&REFSTDOUT";
	}
	else {

		#child process $pid = 0

		PrintLog( "PCL Start...\n", $iDebugLevel >= 1 );
		system( "$pcl" );
		PrintLog( "PCL End!\n", $iDebugLevel >= 1 );

		PrintLog( "Child Exit!!!\n" );

		exit 0;
	}

	PrintLog( "Simulator End!\n" );

}

sub PrintTDDResult {
	my ( $tddResult, $tddNGResult, $csvResult, $iJobNo ) = @_;
	my $sendFile = $TDDInfoHash{"Job$iJobNo"}{"$keySend"};

	#test start
	print $tddResult "Job$iJobNo $sendFile {\n";
	print ALLTDDRESULT "Job$iJobNo $sendFile {\n";
	print $tddNGResult "Job$iJobNo $sendFile {\n";
	print ALLTDDNGRESULT "Job$iJobNo $sendFile {\n";

	#job check
	PrintLog( "+++++ Job $iJobNo Processing... +++++\n" );
	my $TDDCheckHash = $TDDInfoHash{"Job$iJobNo"}{"Hash$keyCheck"};
	my $JobCheckHash = $LogInfoHash{"Job$iJobNo"};

	foreach (keys %$TDDCheckHash) {
		my $tddValue = $$TDDCheckHash{$_};
		my $jobValue = $$JobCheckHash{$_};
		my $result;
		my $bNGItemFound = 0;
		if ( $jobValue eq $tddValue ) {
			$iCheckCount++;
			$result = $resultOKFlag;
		} else {
			$iCheckCount++;
			$iNGCount++;
			$result = $resultNGFlag;
			$bNGItemFound = 1;
		}

		PrintLog( "Check Item = $_\n", $iDebugLevel >= 1 );
		PrintLog( "\ttddValue = $tddValue;\n\tjobValue = $jobValue;\n", $iDebugLevel >= 1 );

		print $tddResult "\t\tcheck $_ = $tddValue\t$result\n";
		print ALLTDDRESULT "\t\tcheck $_ = $tddValue\t$result\n";
		print $tddNGResult "\t\tcheck $_ = $tddValue\t$result (Log value: $jobValue)\n" if ( $bNGItemFound );
		print ALLTDDNGRESULT "\t\tcheck $_ = $tddValue\t$result (Log value: $jobValue)\n" if ( $bNGItemFound );
		print $csvResult "$iJobNo$csvItemSeparator$sendFile$csvItemSeparator$_=$tddValue$csvItemSeparator$result\n";
	}

	#page check
	my $iPageNo;
	for ( $iPageNo = 1 ; $iPageNo <= $PageNumList[$iJobNo] ; $iPageNo++ ) {

		PrintLog( "+++++ Page $iPageNo Processing... +++++\n" );

		my $PageInfoHash  = $LogInfoHash{"Page$iPageNo"};
		my $PageHashRef   = $TDDInfoHash{"Job$iJobNo"}{"Page$iPageNo"};
		my $PageCheckHash = $$PageHashRef{"Hash$keyCheck"};

		my $bPageStart = 0;
		my $bNGPageStart = 0;

		foreach ( keys %$PageCheckHash ) {
			my $tddValue = $$PageCheckHash{"$_"};
			my $jobValue;
			my $result;

			my $bNGItemFound = 0;
			if ( $_ =~ /^(md5sum|CRC)$/i ) {
				if($isCRC){
					$jobValue = $$PageInfoHash{$keyCRC};
				} else {
					$jobValue = $$PageInfoHash{$keyMd5sum};
				}

				if ( $tddValue eq $jobValue ) {
					$iCheckCount++;
					$result = $resultOKFlag;
				}
				else {
					$iCheckCount++;
					$iNGCount++;
					$result = $resultNGFlag;
					$bNGItemFound = 1;
				}
			}
			else {
				$jobValue = $$PageInfoHash{"$_"};

				if ( $tddValue == $jobValue ) {
					$iCheckCount++;
					$result = $resultOKFlag;
				}
				else {
					$iCheckCount++;
					$iNGCount++;
					$result = $resultNGFlag;
					$bNGItemFound = 1;
				}
			}

			PrintLog( "Check Item = $_\n", $iDebugLevel >= 1 );
			PrintLog( "\ttddValue = $tddValue;\n\tjobValue = $jobValue;\n", $iDebugLevel >= 1 );

			print $tddResult "\tPage$iPageNo {\n" unless ( $bPageStart );
			print ALLTDDRESULT "\tPage$iPageNo {\n" unless ( $bPageStart );
			print $tddNGResult "\tPage$iPageNo {\n" if ( $bNGItemFound && !$bNGPageStart );
			print ALLTDDNGRESULT "\tPage$iPageNo {\n" if ( $bNGItemFound && !$bNGPageStart );

			print $tddResult "\t\tcheck $_ = $tddValue\t$result\n";
			print ALLTDDRESULT "\t\tcheck $_ = $tddValue\t$result\n";
			print $tddNGResult "\t\tcheck $_ = $tddValue\t$result (Log value: $jobValue)\n" if ( $bNGItemFound );
			print ALLTDDNGRESULT "\t\tcheck $_ = $tddValue\t$result (Log value: $jobValue)\n" if ( $bNGItemFound );
			print $csvResult "$iJobNo$csvItemSeparator$sendFile$csvItemSeparator$iPageNo$csvItemSeparator$_=$tddValue$csvItemSeparator$result\n";

			$bPageStart = 1;
			$bNGPageStart = 1 if ( $bNGItemFound );
		}

		print $tddResult "\t}\n" if ( $bPageStart );
		print ALLTDDRESULT "\t}\n" if ( $bPageStart );
		print $tddNGResult "\t}\n" if ( $bNGPageStart );
		print ALLTDDNGRESULT "\t}\n" if ( $bNGPageStart );
	}

	PrintLog( "+++++ All Page Processing End! +++++\n" );
	PrintLog( "+++++ Job $iJobNo End!... +++++\n" );

	print $tddResult "}\n";
	print ALLTDDRESULT "}\n";
	print $tddNGResult "}\n";
	print ALLTDDNGRESULT "}\n";
}

sub InterpretLogFile {
	my ( $pclPath, $profPath, $iJobNo, $file ) = @_;

	my $logFile = $pclPath. $profPath . "/". $TDDInfoHash{"Job$iJobNo"}{"$keyJobName"};
	my $pcllogFile = substr( $file, 0, rindex( $file, "/" ) ). "/". $TDDInfoHash{"Job$iJobNo"}{"$keyJobName"}.".log";

	PrintLog( "InterpretLogFile: $logFile...\n" );
	PrintLog( "InterpretLogFile: $pcllogFile...\n" );

	my $bRead      = 0;
	my $bJobStart  = 0;
	my $bPageStart = 0;
	my $key;
	my $value;
	my $hexstring;
	if($isCRC){
		my $crcString;
		my $crcFile;
	}else{
		my $md5String;
		my $rasFile;
	}
	my $line;
	my $iPageNo = 0;
	my $iLineNo = 0;

	open(PCLLOGFILE, $pcllogFile);

	%LogInfoHash = ();
	$LogInfoHash{"$keyViewList"} = ();
	$LogInfoHash{"Job$iJobNo"}{"paper_request"} = "false";
	$LogInfoHash{"Job$iJobNo"}{"page_count"} = 0;

	while(<PCLLOGFILE>){
		chomp($line = $_);
		$iLineNo++;
		if ($line =~ /^\s*$/) {
			next;
		}
		# interpret line
		if ( $line =~ /^\[Job Start\](.*)$/ ) {
			$iPageNo++;
		}
		elsif ( $line =~ /^(.*)\[Page End\](.*)$/ ) {
			$iPageNo++;
		}
		elsif ( $line =~ /^(\[PCL\]0309) (.*)$/ ) {
			$LogInfoHash{"Job$iJobNo"}{"paper_request"} = "true";
		}
		elsif ( $line =~ /^(\[PCL\]0302)(.*)$/ ) {
			$LogInfoHash{"Job$iJobNo"}{"page_count"}++;
		}
		elsif ( $line =~ /^([a-zA-Z0-9_.\[\]]+)\s+(.*)/ ) {
			$key       = $1;
			$hexstring = $2;
			if ( $hexstring =~ /^-?0[xX][0-9a-fA-F]+$/ ) {
				$value = oct $hexstring;
			}
			else {
				$value = $hexstring;
			}
			if( $key eq $keyQty || $key eq $keyColorCount || $key eq $keyOutmode || $key eq $keyBinding  || $key eq $keyFinish 
			|| $key eq $keyStaple || $key eq $keyPunch || $key eq $keyFold ){
				$LogInfoHash{"Job$iJobNo"}{"$key"} = $value unless ( $LogInfoHash{"Job$iJobNo"}{"$key"} );
			}
			else {
				$LogInfoHash{"Page$iPageNo"}{"$key"} = $value unless ( $LogInfoHash{"Page$iPageNo"}{"$key"} );
			}
		}
		#if($line =~ /^\[PCL\]0302 (.*)$/){
		#elsif ($line =~ /^(\[PCL\]0302) (.*)$/){
			#$LogInfoHash{"Job$iJobNo"}{$1} = $2;
			#PrintLog("testaaaaaaaaaaaaaaaaaaaaaaa".$1.$2."\n");
		#}elsif($line =~ /^(\[PCL\]0304) (.*)$/){
			#$LogInfoHash{"Job$iJobNo"}{$1} = $2;
		#}
	}
	close PCLLOGFILE;
	$iLineNo = 0;
	$iPageNo = 0;

	open( LOGFILE, $logFile );

	#%LogInfoHash = ();
	#$LogInfoHash{"$keyViewList"} = ();

	while ( 1 ) {

		#read line
		unless ( $bRead ) {
			last unless ( $line = <LOGFILE> );
			chomp( $line );

			++$iLineNo;
			$bRead = 1;
		}

		# trim line
		if ( $line =~ /^(\s+)(.*)/ ) {
			$line = $2;
		}

		# check blank line
		if ( $line =~ /^\s*$/ ) {
			$bRead = 0;
			next;
		}

		# interpret line
		if ( $line =~ /^gpsPlotOpen(.*)/ ) {
			PrintLog( "gpsPlotOpen\n", $iDebugLevel >= 1 );
			$bJobStart = 1;
			$bRead     = 0;
		}
		elsif ( $line =~ /^gpsPlotClose(.*)/ ) {
			PrintLog( "gpsPlotClose\n", $iDebugLevel >= 1 );
			$bJobStart = 0;
			$bRead     = 0;
		}
		elsif ( $line =~ /^gpsPlotSetPageParamShm(.*)/ ) {
			PrintLog( "gpsPlotSetPageParamShm\n", $iDebugLevel >= 1 );
			die "Error: file: $logFile line: $iLineNo\n\tThe page isn't in Job!" unless ( $bJobStart );

			$iPageNo++ unless ( $bPageStart );
			$bPageStart = 1;
			$bRead      = 0;
		}
		elsif ( $line =~ /^gpsFrameClose(.*)/ ) {
			PrintLog( "gpsFrameClose\n", $iDebugLevel >= 1 );
			die "Error: file: $logFile line: $iLineNo\n\tThe page isn't started!" unless ( $bPageStart );
			die "Error: file: $logFile line: $iLineNo\n\tThe page isn't in Job!" unless ( $bJobStart );

			$bPageStart = 0;
			$bRead      = 0;
			if($isCRC){
				my $allpageno = 0;
				$allpageno = sprintf("%06d",$iPageNo);
				open CRC,">> $crcChecklist";
				$crcFile = join( ".","page", $TDDInfoHash{"Job$iJobNo"}{"$keyJobName"}, $allpageno, "crc");
				my $target = join (".", $TDDInfoHash{"Job$iJobNo"}{$keyJobName},"page",$allpageno, "crc ");
				open CRCFILE, $gpsconfHash{"output"}."/".$crcFile;
				chomp ($crcString = <CRCFILE>);
				$LogInfoHash{"Page$iPageNo"}{$keyCRC} = $crcString;
				#print "\tPage $iPageNo CRC = $crcString\n" if($iDebugLevel >= 1);
				print CRC $target."\t".$crcString."\n";
				PrintLog( "CRC " . $gpsconfHash{"output"} . "/" . $crcFile."\n", $iDebugLevel >= 1 );
				PrintLog( "\tPage $allpageno CRC = $crcString\n", $iDebugLevel >= 1 );
				close CRCFILE;
				close CRC;
			}else{
				$rasFile = join( ".","page", $TDDInfoHash{"Job$iJobNo"}{"$keyJobName"}, $iPageNo, "ras", $viewCopySuffix );
				$pngFile = join( ".","page", $TDDInfoHash{"Job$iJobNo"}{"$keyJobName"}, $iPageNo, "ras", "png" );
				my $rasFilePath = "./".$gpsconfHash{"output"}."/".$rasFile;
				my $pngFilePath = "./".$gpsconfHash{"output"}."/".$pngFile;
				my $objFilePath = substr( $file, 0, rindex( $file, "/" ) ). "/".$pngFile;
				`./$ras2pngScript $rasFilePath`;
				`cp $rasFilePath $objFilePath`;
				`rm -rf $pngFilePath`;

				push @{ $LogInfoHash{"$keyViewList"} }, $rasFile;

				open MD5SUMIN, "md5sum " . $gpsconfHash{"output"} . "/" . $rasFile . "|";
				$md5string = <MD5SUMIN>;
				chomp( $md5string );
				$md5string =~ /(^\S+)\s+(\S+)/;
				$LogInfoHash{"Page$iPageNo"}{"$keyMd5sum"} = $1;

				PrintLog( "md5sum " . $gpsconfHash{"output"} . "/" . $rasFile."\n", $iDebugLevel >= 1 );
				PrintLog( "\tPage $iPageNo md5sum = $1\n", $iDebugLevel >= 1 );

				close MD5SUMIN;
			}
		}
		elsif ( $line =~ /^gpsFrameCancel(.*)/ ) {
			PrintLog( "gpsFrameCancel\n", $iDebugLevel >= 1 );

			$bRead     = 0;
		}
		elsif ( $line =~ /^([a-zA-Z0-9_.\[\]]+)\s+(.*)/ ) {
			$key       = $1;
			$hexstring = $2;

			if ( $hexstring =~ /^-?0[xX][0-9a-fA-F]+$/ ) {
				$value = oct $hexstring;
			}
			else {
				$value = $hexstring;
			}

			$LogInfoHash{"Page$iPageNo"}{"$key"} = $value unless ( $LogInfoHash{"Page$iPageNo"}{"$key"} );

			$bRead = 0;
		}
		else {
			$bRead = 0;
		}
	}

	#debug info
	if ( $iDebugLevel >= 2 ) {
		PrintLog( "-+-+-+-+-+- DEBUG INFO START -+-+-+-+-+-\n" );
		my $LogCheckHash = $LogInfoHash{"Page$iPageNo"};
		foreach ( keys %$LogCheckHash ) {
			PrintLog( "\t$_ = $$LogCheckHash{$_}\n" );
		}
		PrintLog( "-+-+-+-+-+- DEBUG INFO END -+-+-+-+-+-\n" );
	}
}

sub InterpretTDDFile {
	my ( $file ) = @_;

	PrintLog( "InterpretTDDFile: $file...\n" );

	my $bRead                 = 0;
	my $bPclPath              = 0;
	my $bJobStart             = 0;
	my $bPageStart            = 0;
	my $bBlockStart           = 0;
	my $bPatch                = 0;
	my $bSend                 = 0;
	my $bSet                  = 0;
	my $bJobCheck             = 0;
	my $bPageCheck            = 0;
	my $bKey                  = 0;
	my $bValue                = 0;
	my $bReadString           = 0;
	my $iJobBlockStartTagCnt  = 0;
	my $iPageBlockStartTagCnt = 0;
	my $item;
	my $key;
	my $value;
	my $hexstring;
	my $line;
	my $iJobNo;
	my $iPageNo;
	my $iLineNo     = 0;
	my $iCurrPageNo = 0;

	open( TDDFILE, $file );

	while ( 1 ) {

		#read line
		unless ( $bRead ) {
			last unless ( $line = <TDDFILE> );
			chomp( $line );

			++$iLineNo;
			$bRead = 1;
		}

		# trim line
		if ( $line =~ /^(\s+)(.*)/ ) {
			$line = $2;
		}

		# check blank line
		if ( $line =~ /^\s*$/ ) {
			$bRead = 0;
			next;
		}

		if ( $line =~ /^#(.*)/ ) {
			$bRead = 0;
			next;
		}

		# interpret line
		if ( $line =~ /^{(.*)/ ) {
			$line = $1;

			$bBlockStart = 1;

			if ( $bPageStart ) {
				$TDDInfoHash{"Job$JobNum"}{"Page$PageNumList[$JobNum]"} = {};
				$iPageBlockStartTagCnt++;
			}
			elsif ( $bJobStart ) {
				$TDDInfoHash{"Job$JobNum"} = {};
				$iJobBlockStartTagCnt++;
			}
			else {
				die "Error: file: $file line: $iLineNo\n\tThere is no Block Command before \"{\"!";
			}
		}
		elsif ( $line =~ /^}(.*)/ ) {
			$line = $1;

			$bBlockStart = 0;

			if ( $bPageStart ) {
				$bPageStart = 0 unless ( --$iPageBlockStartTagCnt );
			}
			elsif ( $bJobStart ) {
				$bJobStart = 0 unless ( --$iJobBlockStartTagCnt );
			}
		}
		elsif ( $bPageStart && !$iPageBlockStartTagCnt && $line =~ /^([0-9]+)(.*)/ ) {
			$line        = $2;
			$iCurrPageNo = $1;

			if ( $iCurrPageNo >= $PageNumList[$JobNum] ) {
				$PageNumList[$JobNum] = $iCurrPageNo;
			}
			else {
				die "Error: file: $file line: $iLineNo\n\tThe specified page No. is must bigger than before!";
			}
		}
		elsif ( $line =~ /^"(.*)/ ) {
			if ( $line =~ /^"(.*)"(.*)/ ) {
				$line = $2;

				$item        = $1;
				$bReadString = 1;
			}
			else {
				die "Error: file: $file line: $iLineNo\n\tCan't find the end of string!";
			}

			if ( $bKey == 1 ) {
				$key = $item;
			}
			if ( $bValue == 1 ) {
				$value = $item;
			}
		}
		elsif ( $bPclPath ) {
			if ( $bReadString ) {
				if ( $bJobStart ) {
					$TDDInfoHash{"Job$JobNum"}{"$keyPclPath"} = $item;
				}
				else {
					$TDDInfoHash{"$keyPclPath"} = $item;
				}
				$bReadString = 0;
			}
			elsif ( $line =~ /^([a-zA-Z0-9_.\[\]]+)(.*)/ ) {
				$line = $2;

				$value = $1;
				if ( $bJobStart ) {
					$TDDInfoHash{"Job$JobNum"}{"$keyPclPath"} = $value;
				}
				else {
					$TDDInfoHash{"$keyPclPath"} = $value;
				}
			}

			$bPclPath = 0;
		}
		elsif ( $bPatch ) {
			if ( $bReadString ) {
				$TDDInfoHash{"Job$JobNum"}{"$keyPatch"} = $item;
				$bReadString = 0;
			}
			elsif ( $line =~ /^([a-zA-Z0-9_.\[\]]+)(.*)/ ) {
				$line = $2;

				$value = $1;
				$TDDInfoHash{"Job$JobNum"}{"$keyPatch"} = $value;
			}
			$bPatch = 0;
		}
		elsif ( $bSend ) {
			if ( $bReadString ) {
				$TDDInfoHash{"Job$JobNum"}{"$keySend"} = $item;

				my $iNameIndex = rindex( $item, "/" );
				my $name = substr( $item, $iNameIndex + 1 );

				$TDDInfoHash{"Job$JobNum"}{"$keyJobName"} = $name;

				$bReadString = 0;
			}
			elsif ( $line =~ /^(\S+)\s*(.*)/ ) {
				$line = $2;

				$value = $1;
				$TDDInfoHash{"Job$JobNum"}{"$keySend"} = $value;

				my $iNameIndex = rindex( $value, "/" );
				my $name = substr( $value, $iNameIndex + 1 );

				$TDDInfoHash{"Job$JobNum"}{"$keyJobName"} = $name;
			}
			$bSend = 0;
		}
		elsif ( $bSet ) {
			if ( $bKey == 1 ) {
				if ( $bReadString ) {
					$bReadString = 0;
				}
				elsif ( $line =~ /^([a-zA-Z0-9_.\[\]]+)(.*)/ ) {
					$line = $2;

					$key = $1;
				}
				elsif ( $line =~ /^=(.*)/ ) {
					$line = $1;

					$bKey   = 0;
					$bValue = 1;
				}
			}
			elsif ( $bValue == 1 ) {
				if ( $bReadString ) {
					$TDDInfoHash{"Job$JobNum"}{"Hash$keySet"}{"$key"} = $value;
					$bReadString = 0;
				}
				elsif ( $line =~ /^([a-zA-Z0-9_.\[\]]+)(.*)/ ) {
					$line      = $2;
					$hexstring = $1;

					if ( $hexstring =~ /^-?0[xX][0-9a-fA-F]+$/ ) {
						$value = oct $hexstring;
					}
					else {
						$value = $hexstring;
					}
					$TDDInfoHash{"Job$JobNum"}{"Hash$keySet"}{"$key"} = $value;
				}

				$bValue = 0;
				$bSet   = 0;
			}
		}
		elsif ( $bJobCheck ) {
			if ( $bKey == 1 ) {
				if ( $bReadString ) {
					$bReadString = 0;
				}
				elsif ( $line =~ /^([a-zA-Z0-9_.\[\]]+)(.*)/ ) {
					$line = $2;

					$key = $1;
				}
				elsif ( $line =~ /^=(.*)/ ) {
					$line = $1;

					$bKey   = 0;
					$bValue = 1;
				}
			}
			elsif ( $bValue == 1 ) {
				if ( $bReadString ) {
					$TDDInfoHash{"Job$JobNum"}{"Hash$keyCheck"}{"$key"} =
					  $value;
					$bReadString = 0;
				}
				elsif ( $line =~ /^([a-zA-Z0-9_.\[\]]+)(.*)/ ) {
					$line      = $2;
					$hexstring = $1;

					if ( $hexstring =~ /^-?0[xX][0-9a-fA-F]+$/ ) {
						$value = oct $hexstring;
					}
					else {
						$value = $hexstring;
					}
					$TDDInfoHash{"Job$JobNum"}{"Hash$keyCheck"}{"$key"} =
					  $value;
				}

				$bValue    = 0;
				$bJobCheck = 0;
			}
		}
		elsif ( $bPageCheck ) {
			if ( $bKey == 1 ) {
				if ( $bReadString ) {
					$bReadString = 0;
				}
				elsif ( $line =~ /^([a-zA-Z0-9_.\[\]]+)(.*)/ ) {
					$line = $2;

					$key = $1;
				}
				elsif ( $line =~ /^=(.*)/ ) {
					$line = $1;

					$bKey   = 0;
					$bValue = 1;
				}
			}
			elsif ( $bValue == 1 ) {
				if ( $bReadString ) {
					$TDDInfoHash{"Job$JobNum"}{"Page$PageNumList[$JobNum]"}{"Hash$keyCheck"}{"$key"} = $value;
					$bReadString = 0;
				}
				elsif ( $line =~ /^([a-zA-Z0-9_.\[\]]+)(.*)/ ) {
					$line      = $2;
					$hexstring = $1;

					# md5sum check
					if ( $key =~ /^(md5sum|CRC)$/i ) {
						$value = $hexstring;
					}
					elsif ( $hexstring =~ /^-?0[xX][0-9a-fA-F]+$/ ) {
						$value = oct $hexstring;
					}
					else {
						$value = $hexstring;
					}
					$TDDInfoHash{"Job$JobNum"}{"Page$PageNumList[$JobNum]"}{"Hash$keyCheck"}{"$key"} = $value;
				}

				$bValue     = 0;
				$bPageCheck = 0;
			}
		}
		elsif ( $line =~ /^([a-zA-Z0-9_.\[\]]+)(.*)/ ) {
			$line = $2;

			$item = $1;

			if ( $item =~ /^PclPath$/i ) {
				$bPclPath = 1;
			}
			elsif ( $item =~ /^Job$/i ) {
				die "Error: file: $file line: $iLineNo\n\tThe Job can't be in Job!" if ( $bJobStart );
				die "Error: file: $file line: $iLineNo\n\tError: The Job can't be in Page!" if ( $bPageStart );

				$bJobStart = 1;
				$JobNum++;
				$PageNumList[$JobNum] = 0;
			}
			elsif ( $item =~ /^Page$/i ) {
				die "Error: file: $file line: $iLineNo\n\tThe page isn't in Job!" unless ( $bJobStart );
				die "Error: file: $file line: $iLineNo\n\tThe page can't be in page!" if ( $bPageStart );

				$bPageStart = 1;
				$PageNumList[$JobNum]++;
			}
			elsif ( $item =~ /^Send$/i ) {
				$bSend = 1;
			}
			elsif ( $item =~ /^Patch$/i ) {
				$bPatch = 1;
			}
			elsif ( $item =~ /^Set$/i ) {
				$bKey = 1;
				$bSet = 1;
			}
			elsif ( $item =~ /^Check$/i ) {
				$bKey = 1;
				if ( $bPageStart ) {
					$bPageCheck = 1;
				}
				elsif ( $bJobStart ) {
					$bJobCheck = 1;
				}
			}
		}
		else {
			$line = substr( $line, 1 );
		}
	}

	close TDDFILE;

	# modify the pcl path
	if ( exists $TDDInfoHash{"$keyPclPath"} ) {
		if ( $TDDInfoHash{"$keyPclPath"} !~ /\/$/ ) {
			$TDDInfoHash{"$keyPclPath"} = $TDDInfoHash{"$keyPclPath"} . "/";
		}
	}
	else {
		$TDDInfoHash{"$keyPclPath"} = "./";
	}

	for ( $iJobNo = 1 ; $iJobNo <= $JobNum ; $iJobNo++ ) {
		if ( exists $TDDInfoHash{"Job$iJobNo"}{"$keyPclPath"} ) {
			if ( $TDDInfoHash{"Job$iJobNo"}{"$keyPclPath"} !~ /\/$/ ) {
				$TDDInfoHash{"Job$iJobNo"}{"$keyPclPath"} = $TDDInfoHash{"Job$iJobNo"}{"$keyPclPath"} . "/";
			}
		}
	}

	# debug info
	if ( $iDebugLevel >= 2 ) {
		PrintLog( "-+-+-+-+-+- DEBUG INFO START -+-+-+-+-+-\n" );
		for ( $iJobNo = 1; $iJobNo <= $JobNum; $iJobNo++ ) {
			my $sendFile = $TDDInfoHash{"Job$iJobNo"}{"$keySend"};
			PrintLog( "Job$iJobNo $sendFile {\n" );

			for ( $iPageNo = 1; $iPageNo <= $PageNumList[$iJobNo]; $iPageNo++ )
			{
				PrintLog( "\tPage$iPageNo {\n" );

				my $PageCheckHash = $TDDInfoHash{"Job$iJobNo"}{"Page$iPageNo"}{"Hash$keyCheck"};
				foreach ( keys %$PageCheckHash ) {
					PrintLog( "\t\tcheck $_ = $$PageCheckHash{$_}\n" );
				}

				PrintLog( "\t}\n" );
			}

			PrintLog( "}\n" );
		}
		PrintLog( "-+-+-+-+-+- DEBUG INFO END -+-+-+-+-+-\n" );
	}
}

sub InterpretGpsconfigFile {
	PrintLog( "InterpretGpsconfigFile...\n" );
	my ( $gcFile ) = @_;
	my $gcKey;
	my $gcValue;
	my $gcLine;

	open GPSCONFIGFILE, "$gcFile";

	PrintLog( "-+-+-+-+-+- DEBUG INFO START -+-+-+-+-+-\n", $iDebugLevel >= 2 );

	%gpsconfHash = ();
	while ( $gcLine = <GPSCONFIGFILE> ) {
		next if ( $gcLine =~ /^\s*$/ );
		chomp( $gcLine );

		( $gcKey, $gcValue ) = split( /\s{2,}/, $gcLine );

		$gpsconfHash{$gcKey} = $gcValue;

		PrintLog( "\t$gcKey = $gcValue\n", $iDebugLevel >= 2 );
	}

	PrintLog( "-+-+-+-+-+- DEBUG INFO END -+-+-+-+-+-\n", $iDebugLevel >= 2 );

	close GPSCONFIGFILE;
}

sub InterpretVariableFile {
	PrintLog( "InterpretVariableFile...\n" );
	my ( $vaFile ) = @_;
	my $vaKey;
	my $vaValue;
	my $vaLine;

	open VARIABLEFILE, "$vaFile";

	PrintLog( "-+-+-+-+-+- DEBUG INFO START -+-+-+-+-+-\n", $iDebugLevel >= 2 );

	%variableHash = ();
	while ( $vaLine = <VARIABLEFILE> ) {
		next if ( $vaLine =~ /^\s*$/ );
		chomp( $vaLine );

		$vaLine =~ /(^\S+)\s+(.+)/;
		( $vaKey, $vaValue ) = ( $1, $2 );

		$variableHash{$vaKey} = $vaValue;

		PrintLog( "\t$vaKey = $vaValue\n", $iDebugLevel >= 2 );
	}

	PrintLog( "-+-+-+-+-+- DEBUG INFO END -+-+-+-+-+-\n", $iDebugLevel >= 2 );

	close VARIABLEFILE;
}

sub UpdateGpsconfigFile {
	PrintLog( "UpdateGpsconfigFile...\n" );
	my ( $gcFile ) = @_;
	my $gcKey;
	my $gcValue;

	open GPSCONFIGFILE, "> $gcFile";

	PrintLog( "-+-+-+-+-+- DEBUG INFO START -+-+-+-+-+-\n", $iDebugLevel >= 2 );

	foreach ( keys %gpsconfHash ) {
		$gcKey   = $_;
		$gcValue = $gpsconfHash{$gcKey};
		print GPSCONFIGFILE "$gcKey\t$gcValue\n";

		PrintLog( "\t$gcKey = $gcValue\n", $iDebugLevel >= 2 );
	}

	PrintLog( "-+-+-+-+-+- DEBUG INFO END -+-+-+-+-+-\n", $iDebugLevel >= 2 );

	close GPSCONFIGFILE;
}

sub UpdateVariableFile {
	PrintLog( "UpdateVariableFile...\n" );
	my ( $vaFile ) = @_;
	my $vaKey;
	my $vaValue;

	PrintLog( "-+-+-+-+-+- DEBUG INFO START -+-+-+-+-+-\n", $iDebugLevel >= 2 );

	open VARIABLEFILE, "> $vaFile";
	foreach ( keys %variableHash ) {
		$vaKey   = $_;
		$vaValue = $variableHash{$vaKey};
		print VARIABLEFILE "$vaKey\t$vaValue\n";

		PrintLog( "\t$vaKey = $vaValue\n", $iDebugLevel >= 2 );
	}

	PrintLog( "-+-+-+-+-+- DEBUG INFO END -+-+-+-+-+-\n", $iDebugLevel >= 2 );

	close VARIABLEFILE;
}

sub PrintLog {
	my ( $msg, $bPrint ) = @_;
	$bPrint = 1 unless defined ( $bPrint );

	print $msg if $bPrint;
	print $hLogFile $msg if ( $bPrint && $bLogFile)
}

sub checkIP{
	my ($ip) = @_;
	my $ret = 0;
	if($ip =~ /^(\d{1,3})\.(\d{1,3})\.(\d{1,3})\.(\d{1,3})$/ ){
		for(my $i = 1; $i <= 4; $i++){
			if($$i < 0 || $$i > 255){
				#Invalid IP
				$ret = -1;
				last;
			}
		}

		if($ret == 0){	
			#check host is reachable or not
			my $p = Net::Ping->new();
			if($p->ping($ip)) {
				#host is reachable
				$ret = 0;
			}else{
				#host is unreachable
				$ret = -2;
			}
			$p->close();
		}
		
	}else {
		#Invalid IP
		$ret = -1;
	}
	return $ret;
}
