
// (C) 2023 e6nlaq
// Try Aqua

let output = [];
let va = {};

function isstring(s) {
	if (s[0] == '"' && s[s.length - 1] == '"') return true;
	else return false;
}

function cutstr(s) {
	return s.substr(1, s.length - 2);
}

function scriptcut(code) {
	let ret = [];
	let tmp = "";
	let isstr = false;

	for (let i = 0; i < code.length; i++) {
		if (code[i] == '"') {
			isstr = !isstr;
		} else if (!isstr && code[i] == " ") {
			ret.push(tmp);
			tmp = "";
			continue;
		}

		tmp += code[i];
	}

	ret.push(tmp);

	return ret;

}

function aqua(script) {
	let code = scriptcut(script);
	console.log(code);

	if (code[0][0] === "#") return "undefined";

	switch (code[0]) {
		case "outf":
			console.log(cutstr(code[1]));
			if (isstring(code[1])) output.push(cutstr(code[1]));
	}
}

function run(script_full) {
	let script = script_full.split("\n");

	for (let i = 0; i < script.length; i++) {
		// try {
		aqua(script[i]);
		// } catch (error) {
		// output = ["<Error>"];
		// }

	}

	let out = document.getElementById("output");
	out.textContent = "";
	output.forEach(function (line) {
		out.textContent += line;
	});
}
