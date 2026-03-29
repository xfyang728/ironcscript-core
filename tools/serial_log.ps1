# K210 串口日志接收工具
# 用法: powershell -File serial_log.ps1 [COM端口] [波特率]
# 示例: powershell -File serial_log.ps1 COM9 115200

param(
    [string]$Port = "COM9",
    [int]$BaudRate = 115200,
    [string]$OutputFile = "d:\MyCode\CScriptEngine\examples\out.s"
)

$buffer = New-Object System.Collections.ArrayList

Write-Host "连接到 $Port @ $BaudRate bps..."
Write-Host "日志将输出到: $OutputFile"
Write-Host "按 Ctrl+C 退出`n"

try {
    $serialPort = New-Object System.IO.Ports.SerialPort $Port, $BaudRate
    $serialPort.Open()
    $serialPort.ReadTimeout = 1000

    while ($serialPort.IsOpen) {
        try {
            $line = $serialPort.ReadLine()
            if ($line) {
                $null = $buffer.Add($line)
                Write-Host $line
            }
        }
        catch [TimeoutException] {
            # 超时，继续等待
        }
        catch {
            break
        }
    }

    $serialPort.Close()
}
catch {
    Write-Host "错误: $_"
}
finally {
    if ($buffer.Count -gt 0) {
        $buffer | Out-File -FilePath $OutputFile -Encoding utf8
        Write-Host "`n日志已保存到: $OutputFile"
    }
}
