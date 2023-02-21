{ pkgs ? import <nixpkgs> {} }:

let lib = pkgs.lib;

	llvmPackages = pkgs.llvmPackages_latest;
	clang-unwrapped = llvmPackages.clang-unwrapped;
	clang = llvmPackages.clang;

	# clangd hack.
	clangd = pkgs.writeScriptBin "clangd" ''
	    #!${pkgs.stdenv.shell}
		export CPATH="$(${clang}/bin/clang -E - -v <<< "" \
			|& ${pkgs.gnugrep}/bin/grep '^ /nix' \
			|  ${pkgs.gawk}/bin/awk 'BEGIN{ORS=":"}{print substr($0, 2)}' \
			|  ${pkgs.gnused}/bin/sed 's/:$//')"
		export CPLUS_INCLUDE_PATH="$(${clang}/bin/clang++ -E - -v <<< "" \
			|& ${pkgs.gnugrep}/bin/grep '^ /nix' \
			|  ${pkgs.gawk}/bin/awk 'BEGIN{ORS=":"}{print substr($0, 2)}' \
			|  ${pkgs.gnused}/bin/sed 's/:$//')"
	    ${clang-unwrapped}/bin/clangd
	'';

	serve = pkgs.writeShellScriptBin
		"serve"
		"cd output && ${pkgs.python3}/bin/python3 -m http.server";

in pkgs.mkShell {
	buildInputs = with pkgs; [
		python3
		serve
		cmark-gfm
		chroma
		chromium
		perl
		gomplate
		gcc
		gdb
	] ++ [
		clangd
		clang
	];

	TOOLS_DIR = "${builtins.toString ./tools}";
	PROJECT_DIR = "${builtins.toString ./.}";

	CXXFLAGS =
		lib.concatStringsSep " "
			(lib.splitString "\n"
				(builtins.readFile ./compile_flags.txt));
}
