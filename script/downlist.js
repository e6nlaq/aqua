
let latest_tag = "";
let latest_version = "";
let preview_tag = "";
let preview_version = "";

window.onload = async function () {
	let res = await fetch("https://api.github.com/repos/e6nlaq/aqua/releases");
	let version = await res.json();

	preview_version = version[0]["name"];
	preview_tag = version[0]["tag_name"];

	for (let i = 0; i < 10; i++) {
		let tmp = version[i];
		if (!tmp["prerelease"]) {
			latest_tag = tmp["tag_name"];
			latest_version = tmp["name"];
			break;
		}
	}

	document.getElementById('latest_msi').setAttribute('href', `https://github.com/e6nlaq/aqua/releases/download/${latest_tag}/Aqua.Windows.Setup.msi`);
	document.getElementById('preview_msi').setAttribute('href', `https://github.com/e6nlaq/aqua/releases/download/${preview_tag}/Aqua.Windows.Setup.msi`);

	document.getElementById('latest_sh').setAttribute('href', `https://github.com/e6nlaq/aqua/releases/download/${latest_tag}/install-linux.sh`);
	document.getElementById('preview_sh').setAttribute('href', `https://github.com/e6nlaq/aqua/releases/download/${preview_tag}/install-linux.sh`);

	document.getElementById('latest_zip').setAttribute('href', `https://github.com/e6nlaq/aqua/archive/refs/tags/${latest_tag}.zip`);
	document.getElementById('preview_zip').setAttribute('href', `https://github.com/e6nlaq/aqua/archive/refs/tags/${preview_tag}.zip`);

	document.getElementById('latest_tg').setAttribute('href', `https://github.com/e6nlaq/aqua/archive/refs/tags/${latest_tag}.tar.gz`);
	document.getElementById('preview_tg').setAttribute('href', `https://github.com/e6nlaq/aqua/archive/refs/tags/${preview_tag}.tar.gz`);

}
