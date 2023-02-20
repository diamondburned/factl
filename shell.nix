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
		serve
		cmark-gfm
		chroma
		perl
		gomplate
		gcc
		gdb
	] ++ [
		clangd
		clang
	];

	shellHook = ''
		export TOOLS_DIR = "${builtins.toString ./tools}";
		export PROJECT_DIR=${builtins.toString ./.}
		export CXXFLAGS="$(cat compile_flags.txt)"
	'';
}
