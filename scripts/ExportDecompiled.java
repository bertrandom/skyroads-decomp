// Headless post-script: decompile every function and write them to one C file.
// Usage: analyzeHeadless ... -postScript ExportDecompiled.java <output.c>
import java.io.PrintWriter;

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileOptions;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;

public class ExportDecompiled extends GhidraScript {
	@Override
	protected void run() throws Exception {
		String out = getScriptArgs().length > 0 ? getScriptArgs()[0] : "decompiled.c";
		DecompInterface ifc = new DecompInterface();
		ifc.setOptions(new DecompileOptions());
		ifc.openProgram(currentProgram);

		int ok = 0, failed = 0;
		try (PrintWriter w = new PrintWriter(out)) {
			w.printf("// Decompiled from %s by Ghidra%n%n", currentProgram.getName());
			for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
				monitor.checkCancelled();
				DecompileResults r = ifc.decompileFunction(f, 120, monitor);
				w.printf("// ---- %s @ %s ----%n", f.getName(), f.getEntryPoint());
				if (r != null && r.decompileCompleted()) {
					w.println(r.getDecompiledFunction().getC());
					ok++;
				} else {
					w.printf("// decompilation failed: %s%n%n", r == null ? "null" : r.getErrorMessage());
					failed++;
				}
			}
		}
		ifc.dispose();
		println("Decompiled " + ok + " functions (" + failed + " failed) -> " + out);
	}
}
