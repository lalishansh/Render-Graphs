param(
	[string][Parameter(Mandatory)]$Name
)

$Name = $Name -replace '[^a-zA-Z0-9_-]','' -replace '_+','_' -replace '-+','-'

$NameUpper = $Name.ToUpper() -replace '[^A-Z0-9]','_'

$file = "$PSScriptRoot/$Name"
if (Test-Path $file) {
	Write-Error "File already exists: $file"
	# wait for any key press
	[void][System.Console]::ReadKey($true)
	return
} else {
	New-Item -ItemType File -Path $file -Force | Out-Null
	Write-Host "Created file: $file"
}

Set-Content -Path $file -Value @"
#if !defined(WARNINGS_SUPPRESSION_ACTIVE)
	#error "File included directly outside of warnings suppression scope."
#endif

#if !WARNINGS_SUPPRESSION_ACTIVE
	#undef WARNINGS_SUPPRESSED_FOR_$NameUpper
#elif !defined(WARNINGS_SUPPRESSED_FOR_$NameUpper)
	#define  WARNINGS_SUPPRESSED_FOR_$NameUpper

	#define __warning_id__         \
		ON_CLANG_COMPILER("$Name") \
	//	ON_GCC_COMPILER("$Name") \
	//	ON_MSVC_COMPILER(0000) \
	//

	#if COMPILER_HAS_WARNING(__warning_id__)
		SUPPRESS_WARNING(__warning_id__)
	#endif
	#undef __warning_id__
#endif
"@

# open file in txt editor

foreach ($editor in @('code', 'codium', 'notepad', 'notepad++', 'sublime_text', 'atom', 'vim')) {
	$editor_path = (Get-Command $editor -ErrorAction SilentlyContinue).Path
	if ($editor_path) {
		& $editor_path $file
		break
	}
}