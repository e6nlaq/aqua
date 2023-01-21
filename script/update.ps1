
# Aqua Update Program

# Remove-Item './temp/*.*'

Param([String]$path='./temp',[String]$file='./data/update_version_data.dat')


# ファイルをダウンロードするためのWebClientオブジェクトを生成
$cli = New-Object System.Net.WebClient
# ファイルリストから順にURLを抽出
foreach($url in Get-Content $file){
    # 取り出したURLからファイル名を取り出し、変数$fileにセット
  $uri = New-Object System.Uri($url)
  $file = Split-Path $uri.AbsolutePath -Leaf
    # 指定されたURLからファイルをダウンロードし、同名のファイル名で保存
  $cli.DownloadFile($uri, (Join-Path $path $file))}
  