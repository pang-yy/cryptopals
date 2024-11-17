$main = "main.cpp"
$dependencies = @("string-operation.cpp", "util.cpp", "xor.cpp")

$output = "main.exe"

foreach ($file in $dependencies) {
    $objectFile = "$($file -replace '.cpp', '.o')"
    
    clang++ -Wall -c $file -o $objectFile
    
    if ($LASTEXITCODE -ne 0) {
        Write-Host "Compilation of $file failed."
        exit 1
    }
}

clang++ -Wall $main *.o -o $output

if ($LASTEXITCODE -eq 0) {
    Write-Host "Compilation successful."
    Write-Host "Removing object files."
    Remove-Item -Force *.o
    Write-Host "Object files removed."
} else {
    Write-Host "Compilation failed."
}
