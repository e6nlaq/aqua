
let latest_version = "v1.0.0";
let latest_tag = "v1.0.0";
let preview_version = "v1.5.0-pre1";
let preview_tag = "v1.5.0-pre1";
let latest_url = "http://example.com/";
let preview_url = "http://example.com";

let os = platform.os.toString().toLowerCase();

function check_os(name) {
	return os.indexOf(name) !== -1;
}

function change_file(name) {
	latest_url = `https://github.com/e6nlaq/aqua/releases/download/${latest_tag}/${name}`;
	preview_url = `https://github.com/e6nlaq/aqua/releases/download/${preview_tag}/${name}`;
}

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

	let ot = document.getElementById("download_file");

	console.log(os);
	if (check_os("windows")) {
		ot.textContent = "Windows(.msi)";
		change_file("Aqua.Windows.Setup.msi");
	} else if (check_os("os x") || check_os("linux") || check_os("ubuntu") || check_os("macintosh")
		|| check_os("ios") || check_os("android") || check_os("debian")) {
		ot.textContent = "Unix(.sh)";
		change_file("install-linux.sh");
	}
	else if (check_os("chrome os")) {
		ot.textContent = "Source(.zip)";
		latest_url = `https://github.com/e6nlaq/aqua/archive/refs/tags/${latest_tag}.zip`;
		preview_url = `https://github.com/e6nlaq/aqua/archive/refs/tags/${preview_tag}.zip`;
	}
	else {
		ot.textContent = "Source(.tar.gz)";
		latest_url = `https://github.com/e6nlaq/aqua/archive/refs/tags/${latest_tag}.tar.gz`;
		preview_url = `https://github.com/e6nlaq/aqua/archive/refs/tags/${preview_tag}.tar.gz`;
	}

	document.getElementById('latest').textContent = latest_version;
	document.getElementById('preview').textContent = preview_version;

	if (latest_version == preview_version) {
		let delpre = document.getElementById("preview");
		let delp1 = document.getElementById("delp1");
		let delp2 = document.getElementById("delp2");
		delpre.remove(); delp1.remove(); delp2.remove();
	}
};

async function download_latest() {
	window.location.href = latest_url;
	setTimeout('window.location.href="./thanks.html"', 2000);
}

function download_preview() {
	window.location.href = preview_url;
	setTimeout('window.location.href="./thanks.html"', 2000);
}

