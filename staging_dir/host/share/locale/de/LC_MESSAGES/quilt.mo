??    ?      ?  ?   ?	        ?     Z     ~  i  ?  ?  ?  ?  }  y  U  ?  ?  M  ?   J  m   ?  r   c  ?   ?  ?  ?  n  w   [   ?!  `   B"  N   ?"  |  ?"  p  o)  ?  ?+  @   ?-  '  ?-    ?.     0     /0  %   B0  *   h0     ?0  6   ?0     ?0  I   ?0  L   F1  $   ?1     ?1     ?1  $   ?1  E   ?1  !   E2     g2     2  0   ?2     ?2      ?2  -   3     13     M3  ,   i3  !   ?3  (   ?3     ?3      ?3  ,   4     K4     g4     ?4      ?4     ?4     ?4     ?4     5     $5     ?5     ^5     r5  -   ?5      ?5  %   ?5  #   6     +6  0   @6  2   q6  $   ?6     ?6  H   ?6     -7     =7     P7     e7     |7     ?7  =   ?7  D   ?7  $   '8  (   L8  '   u8  !   ?8  +   ?8  .   ?8     9  B   49  9   w9  3   ?9     ?9  #   ?9     #:     9:     Y:     s:     ?:     ?:  '   ?:  &   ?:     ;     (;  ,   @;  A   m;     ?;     ?;     ?;  0   ?;  1   <     N<  #   e<     ?<  %   ?<  #   ?<  <   ?<  &   .=  O   U=  ?   ?=  3   ?>  X   ?>  ,   ?     J?  @   a?  (   ??  )   ??     ??  0   @     E@  =   b@  3   ?@     ?@  ]   ?@  *   QA  d   |A  N   ?A  +   0B     \B  '   xB     ?B  o   ?B  ?   0C  +   ?C  )   D  +   :D  ]   fD     ?D     ?D      ?D     E  7   ,E  .   dE  /   ?E    ?E  V  ?F  e   *H  ]  ?H  ?  ?J  ?  ?N  ?  wP  ?  $R  b  ?T  ?   WW  ?   'X  ?   ?X  ?   0Y  ?  Z  ?  \  h   ?]  ]   ^  9   w^  ?  ?^  ?  \f  ?  ?h  ^   ?j  q  k  B  ?l     ?m     ?m  '   n  D   +n     pn  2   ?n  4   ?n  G   ?n  ?   4o  /   ?o     ?o     	p  %   (p  L   Np  "   ?p     ?p     ?p  :   ?p     4q     Tq  :   tq      ?q  #   ?q  5   ?q  )   *r  .   Tr  !   ?r  !   ?r  :   ?r  #   s     &s     As  &   Vs  5   }s  !   ?s      ?s     ?s  %   t  '   8t     `t      zt  8   ?t  %   ?t  &   ?t  '   !u     Iu  ?   _u  A   ?u  ,   ?u     v  V   .v     ?v     ?v     ?v  #   ?v     ?v     ?v  U   w  V   gw  0   ?w  .   ?w  *   x  )   Ix  8   sx  1   ?x     ?x  [   ?x  ?   Uy  7   ?y     ?y  .   ?y     z  !   2z     Tz  (   sz      ?z     ?z  5   ?z  +   {     ;{  &   W{  5   ~{  f   ?{     |     3|     G|  7   [|  <   ?|     ?|  ,   ?|     }  '   9}  !   a}  d   ?}  -   ?}  W   ~  G  n~  A   ?  u   ?  3   n?     ??  D   ??  .   ??  /   +?  #   [?  5   ?  "   ??  B   ؁  9   ?  %   U?  b   {?  4   ނ  i   ?  V   }?  0   ԃ      ?  ,   &?  $   S?  t   x?  ?   ??  1   ??  0   ؅  1   	?  o   ;?  !   ??     ͆  %   ??     ?  ?   '?  7   g?  <   ??     x   ?       ?   o      t   ?       O   [   ?           Q             1   ?           C       j   ?   y       |   
   I              ?   W      ?   ?                          ?   ?   )   p   ^   Z   k      ?                  e      n   9      -      u       q   F      h   +   '              a   A   ?           D   \   c   d       G       U   ?      8       ?      ]          (   g       2                  	           _       E   *   l   b           !      V   5       R   z   ?   J   ?   ?   <   `       K   .       $      r   ?      ?       6   0       ?   3   ;   @   i   S   4                T   &       B   m   /   ?      ?   ?   :       {   ?   ?      v   P   M       %       f   w   H              "   ?   =   N                  ~   L   #                      ,   ?   }   7   s   Y   >   X          ?    
Add one or more files to the topmost or named patch.  Files must be
added to the patch before being modified.  Files that are modified by
patches already applied on top of the specified patch cannot be added.

-P patch
	Patch to add files to.
 
Edit the specified file(s) in \$EDITOR (%s) after adding it (them) to
the topmost patch.
 
Fork the topmost patch.  Forking a patch means creating a verbatim copy
of it under a new name, and use that new name instead of the original
one in the current series.  This is useful when a patch has to be
modified, but the original version of it should be preserved, e.g.
because it is used in another series, or for the history.  A typical
sequence of commands would be: fork, edit, refresh.

If new_name is missing, the name of the forked patch will be the current
patch name, followed by \`-2'.  If the patch name already ends in a
dash-and-number, the number is further incremented (e.g., patch.diff,
patch-2.diff, patch-3.diff).
 
Generate a dot(1) directed graph showing the dependencies between
applied patches. A patch depends on another patch if both touch the same
file or, with the --lines option, if their modifications overlap. Unless
otherwise specified, the graph includes all patches that the topmost
patch depends on.
When a patch name is specified, instead of the topmost patch, create a
graph for the specified patch. The graph will include all other patches
that this patch depends on, as well as all patches that depend on this
patch.

--all	Generate a graph including all applied patches and their
	dependencies. (Unapplied patches are not included.)

--reduce
	Eliminate transitive edges from the graph.

--lines[=num]
	Compute dependencies by looking at the lines the patches modify.
	Unless a different num is specified, two lines of context are
	included.

--edge-labels=files
	Label graph edges with the file names that the adjacent patches
	modify.

-T ps	Directly produce a PostScript output file.
 
Global options:

--trace
	Runs the command in bash trace mode (-x). For internal debugging.

--quiltrc file
	Use the specified configuration file instead of ~/.quiltrc (or
	@ETCDIR@/quilt.quiltrc if ~/.quiltrc does not exist).  See the pdf
	documentation for details about its possible contents.  The
	special value \"-\" causes quilt not to read any configuration
	file.

--version
	Print the version number and exit immediately. 
Grep through the source files, recursively, skipping patches and quilt
meta-information. If no filename argument is given, the whole source
tree is searched. Please see the grep(1) manual page for options.

-h	Print this help. The grep -h option can be passed after a
	double-dash (--). Search expressions that start with a dash
	can be passed after a second double-dash (-- --).
 
Import external patches.  The patches will be inserted following the
current top patch, and must be pushed after import to apply them.

-p num
	Number of directory levels to strip when applying (default=1)

-R
	Apply patch in reverse.

-P patch
	Patch filename to use inside quilt. This option can only be
	used when importing a single patch.

-f	Overwrite/update existing patches.

-d {o|a|n}
	When overwriting in existing patch, keep the old (o), all (a), or
	new (n) patch header. If both patches include headers, this option
	must be specified. This option is only effective when -f is used.
 
Integrate the patch read from standard input into the topmost patch:
After making sure that all files modified are part of the topmost
patch, the patch is applied with the specified strip level (which
defaults to 1).

-R	Apply patch in reverse.

-q	Quiet operation.

-f	Force apply, even if the patch has rejects. Unless in quiet mode,
	apply the patch interactively: the patch utility may ask questions.

-p strip-level
	The number of pathname components to strip from file names
	when applying patchfile.
 
Please remove all patches using \`quilt pop -a' from the quilt version used to create this working tree, or remove the %s directory and apply the patches from scratch.\n 
Print a list of applied patches, or all patches up to and including the
specified patch in the file series.
 
Print a list of patches that are not applied, or all patches that follow
the specified patch in the series file.
 
Print an annotated listing of the specified file showing which
patches modify which lines. Only applied patches are included.

-P patch
	Stop checking for changes at the specified rather than the
	topmost patch.
 
Print or change the header of the topmost or specified patch.

-a, -r, -e
	Append to (-a) or replace (-r) the exiting patch header, or
	edit (-e) the header in \$EDITOR (%s). If none of these options is
	given, print the patch header.

--strip-diffstat
	Strip diffstat output from the header.

--strip-trailing-whitespace
	Strip trailing whitespace at the end of lines of the header.

--backup
	Create a backup copy of the old version of a patch as patch~.
 
Print the list of files that the topmost or specified patch changes.

-a	List all files in all applied patches.

-l	Add patch name to output.

-v	Verbose, more user friendly output.

--combine patch
	Create a listing for all patches between this patch and
	the topmost or specified patch. A patch name of \`-' is
	equivalent to specifying the first applied patch.

 
Print the name of the next patch after the specified or topmost patch in
the series file.
 
Print the name of the previous patch before the specified or topmost
patch in the series file.
 
Print the name of the topmost patch on the current stack of applied
patches.
 
Refreshes the specified patch, or the topmost patch by default.
Documentation that comes before the actual patch in the patch file is
retained.

It is possible to refresh patches that are not on top.  If any patches
on top of the patch to refresh modify the same files, the script aborts
by default.  Patches can still be refreshed with -f.  In that case this
script will print a warning for each shadowed file, changes by more
recent patches will be ignored, and only changes in files that have not
been modified by any more recent patches will end up in the specified
patch.

-p n	Create a -p n style patch (-p0 or -p1 supported).

-p ab	Create a -p1 style patch, but use a/file and b/file as the
	original and new filenames instead of the default
	dir.orig/file and dir/file names.

-u, -U num, -c, -C num
	Create a unified diff (-u, -U) with num lines of context. Create
	a context diff (-c, -C) with num lines of context. The number of
	context lines defaults to 3.

-z[new_name]
	Create a new patch containing the changes instead of refreshing the
	topmost patch. If no new name is specified, \`-2' is added to the
	original patch name, etc. (See the fork command.)

--no-timestamps
	Do not include file timestamps in patch headers.

--no-index
	Do not output Index: lines.

--diffstat
	Add a diffstat section to the patch header, or replace the
	existing diffstat section.

-f	Enforce refreshing of a patch that is not on top.

--backup
	Create a backup copy of the old version of a patch as patch~.

--sort	Sort files by their name instead of preserving the original order.

--strip-trailing-whitespace
	Strip trailing whitespace at the end of lines.
 
Remove patch(es) from the stack of applied patches.  Without options,
the topmost patch is removed.  When a number is specified, remove the
specified number of patches.  When a patch name is specified, remove
patches until the specified patch end up on top of the stack.  Patch
names may include the patches/ prefix, which means that filename
completion can be used.

-a	Remove all applied patches.

-f	Force remove. The state before the patch(es) were applied will
	be restored from backup files.

-R	Always verify if the patch removes cleanly; don't rely on
	timestamp checks.

-q	Quiet operation.

-v	Verbose operation.
 
Remove the specified or topmost patch from the series file.  If the
patch is applied, quilt will attempt to remove it first. (Only the
topmost patch can be removed right now.)

-n	Delete the next patch after topmost, rather than the specified
	or topmost patch.

-r	Remove the deleted patch file from the patches directory as well.

--backup
	Rename the patch file to patch~ rather than deleting it.
	Ignored if not used with \`-r'.
 
Rename the topmost or named patch.

-P patch
	Patch to rename.
 
Take a snapshot of the current working state.  After taking the snapshot,
the tree can be modified in the usual ways, including pushing and
popping patches.  A diff against the tree at the moment of the
snapshot can be generated with \`quilt diff --snapshot'.

-d	Only remove current snapshot.
 
Upgrade the meta-data in a working tree from an old version of quilt to the
current version. This command is only needed when the quilt meta-data format
has changed, and the working tree still contains old-format meta-data. In that
case, quilt will request to run \`quilt upgrade'.
        quilt --version %s: I'm confused.
 Appended text to header of patch %s\n Applied patch %s (forced; needs refresh)\n Applying patch %s\n Can only refresh the topmost patch with -z currently\n Cannot add symbolic link %s\n Cannot diff patches with -p%s, please specify -p0, -p1, or -pab instead\n Cannot use --strip-trailing-whitespace on a patch that has shadowed files.\n Changes to %s in patch %s reverted\n Commands are: Conversion failed\n Converting meta-data to version %s\n Could not determine the envelope sender address. Please use --sender. Delivery address `%s' is invalid
 Diff failed, aborting\n Directory %s exists\n Display name `%s' contains unpaired parentheses
 Failed to back up file %s\n Failed to backup patch file %s\n Failed to copy files to temporary directory\n Failed to create patch %s\n Failed to import patch %s\n Failed to insert patch %s into file series\n Failed to patch temporary files\n Failed to remove file %s from patch %s\n Failed to remove patch %s\n Failed to remove patch file %s\n Failed to revert changes to %s in patch %s\n File %s added to patch %s\n File %s does not exist\n File %s exists\n File %s is already in patch %s\n File %s is located below %s\n File %s is not being modified\n File %s is not in patch %s\n File %s is unchanged\n File %s may be corrupted\n File %s modified by patch %s\n File %s not found\n File %s removed from patch %s\n File series fully applied, ends at patch %s\n Fork of patch %s created as %s\n Fork of patch %s to patch %s failed\n Importing patch %s (stored as %s)\n Importing patch %s\n Interrupted by user; patch %s was not applied.\n Introduction has no subject header (saved as %s)\n Introduction has no subject header\n Introduction saved as %s\n More recent patches modify files in patch %s. Enforce refresh with -f.\n No next patch\n No patch removed\n No patches applied\n No patches in series\n Nothing in patch %s\n Now at patch %s\n Option \`-P' can only be used when importing a single patch\n Options \`--combine', \`--snapshot', and \`-z' cannot be combined.\n Patch %s already exists in series.\n Patch %s appears to be empty, removing\n Patch %s appears to be empty; applied\n Patch %s can be reverse-applied\n Patch %s does not apply (enforce with -f)\n Patch %s does not exist; applied empty patch\n Patch %s does not exist\n Patch %s does not remove cleanly (refresh it or enforce with -f)\n Patch %s exists already, please choose a different name\n Patch %s exists already, please choose a new name\n Patch %s exists already\n Patch %s exists. Replace with -f.\n Patch %s is applied\n Patch %s is currently applied\n Patch %s is not applied\n Patch %s is not in series\n Patch %s is now on top\n Patch %s is unchanged\n Patch %s needs to be refreshed first.\n Patch %s not applied before patch %s\n Patch %s renamed to %s\n Patch headers differ:\n Patches %s have duplicate subject headers.\n Please use -d {o|a|n} to specify which patch header(s) to keep.\n Refreshed patch %s\n Removed patch %s\n Removing patch %s\n Removing trailing whitespace from line %s of %s
 Removing trailing whitespace from lines %s of %s
 Renaming %s to %s: %s
 Renaming of patch %s to %s failed\n Replaced header of patch %s\n Replacing patch %s with new version\n SYNOPSIS: %s [-p num] [-n] [patch]
 The %%prep section of %s failed; results may be incomplete\n The -v option will show rpm's output\n The quilt meta-data in %s are already in the version %s format; nothing to do\n The quilt meta-data in this tree has version %s, but this version of quilt can only handle meta-data formats up to and including version %s. Please pop all the patches using the version of quilt used to push them before downgrading.\n The topmost patch %s needs to be refreshed first.\n The working tree was created by an older version of quilt. Please run 'quilt upgrade'.\n Unable to extract a subject header from %s\n Unpacking archive %s\n Usage: quilt [--trace[=verbose]] [--quiltrc=XX] command [-h] ... Usage: quilt add [-P patch] {file} ...\n Usage: quilt annotate [-P patch] {file}\n Usage: quilt applied [patch]\n Usage: quilt delete [-r] [--backup] [patch|-n]\n Usage: quilt edit file ...\n Usage: quilt files [-v] [-a] [-l] [--combine patch] [patch]\n Usage: quilt fold [-R] [-q] [-f] [-p strip-level]\n Usage: quilt fork [new_name]\n Usage: quilt graph [--all] [--reduce] [--lines[=num]] [--edge-labels=files] [-T ps] [patch]\n Usage: quilt grep [-h|options] {pattern}\n Usage: quilt header [-a|-r|-e] [--backup] [--strip-diffstat] [--strip-trailing-whitespace] [patch]\n Usage: quilt import [-p num] [-R] [-P patch] [-f] [-d {o|a|n}] patchfile ...\n Usage: quilt new [-p n|-p ab] {patchname}\n Usage: quilt next [patch]\n Usage: quilt pop [-afRqv] [num|patch]\n Usage: quilt previous [patch]\n Usage: quilt push [-afqv] [--merge[=merge|diff3]] [--leave-rejects] [--color[=always|auto|never]] [num|patch]\n Usage: quilt refresh [-p n|-p ab] [-u|-U num|-c|-C num] [-z[new_name]] [-f] [--no-timestamps] [--no-index] [--diffstat] [--sort] [--backup] [--strip-trailing-whitespace] [patch]\n Usage: quilt remove [-P patch] {file} ...\n Usage: quilt rename [-P patch] new_name\n Usage: quilt revert [-P patch] {file} ...\n Usage: quilt setup [-d path-prefix] [-v] [--sourcedir dir] [--fuzz=N] {specfile|seriesfile}\n Usage: quilt snapshot [-d]\n Usage: quilt top\n Usage: quilt unapplied [patch]\n Usage: quilt upgrade\n Warning: more recent patches modify files in patch %s\n Warning: trailing whitespace in line %s of %s
 Warning: trailing whitespace in lines %s of %s
 Project-Id-Version: de
PO-Revision-Date: 2005-07-19 11:32+0200
Last-Translator: Andreas Gruenbacher <agruen@suse.de>
Language-Team:  <en@li.org>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Language: 
X-Generator: KBabel 1.10
 
Fügt eine oder mehrere Dateien zum obersten oder angegebenen Patch
hinzu. Dateien müssen einem Patch hinzugefügt werden, bevor sie
verändert werden. Dateien können einem Patch nur hinzugefügt werden,
solange sie von keinem Patch höher auf dem Stapel verändert werden.

-P patch
	Patch, zu dem die Dateien hinzugefügt werden sollen.
 
Füge die angegebene(n) Datei(en) dem obersten Patch hinzu, und editiere
sie dann in \$EDITOR (%s).
 
Spalte den obersten Patch auf.  Ausfspalten bedeutet, dass eine neue Kopie
des Patches unter einem anderen Namen angelegt wird, und der neue Patch
anstelle des ursprünglichen in die Series-Datei eingetragen wird.  Das ist
praktisch wenn ein Patch verändert werden soll, aber die ursprüngliche Version
erhalten bleiben soll.  Eine typische Abfolge von Befehlen ist: fork, edit, refresh.

Wenn neuer_name fehlt, wird der Name des ursprünglichen Patches verwendet,
gefolgt von \`-2'.  Falls der name bereits in Strich-Nummer endet, wird die
Nummer erhöht (z.B. patch.diff, patch-2.diff, patch-3.diff).
 
Erzeuge einen gerichteten dot(1)-Graphen, der die Abhängigkeiten zwischen
den angewandten Patches zeigt. Ein Patch hängt voni einem anderen ab, wenn
beide dieselbe Datei verändern, oder mit der --lines-Option, wenn sich die
Anderungen in den Patches überlappen. Wenn nicht anders angegeben, zeigt
der Graph alle Patches, von denen der oberste Patch abhängt.
Wenn ein Patchname angegeben wird, wird ein Graph erzeugt, der alle Patches
beinhaltet, von denen der angegebene Patch abhängt, sowie alle, die von
diesem Patch abhängen.

--all	Erzeuge einen Graph, der alle Abhängigkeiten zwischen allen
	angewandten Patches beinhaltet. (Nicht angewandte Patches sind nicht
	beinhaltet.)

--reduce
	Eliminiere transitive Kanten.

--lines[=num]
	Ermittle Abhängigkeiten durch Vergleich der veränderten Zeilen.
	Solange nicht anders angegeben, werden zwei Kontextzeilen angenommen.

--edge-labels=files
	Beschrifte Kanten mit den Namen der betroffenen Dateien.

-T ps	Erzeuge direkt eine PostScript-Datei.
 
Globale Optionen:

--trace
	Führt die Kommandos im bash Trace-Modus (-x) aus. Für Debugging.

--quiltrc datei
	Verwende die angegebene Konfigurationsdatei statt ~/.quiltrc (oder
	@ETCDIR@/quilt.quiltrc, wenn ~/.quiltrc fehlt). Siehe die pdf-Dokumentation
	für mögliche Einstellungen. Der Dateiname \`-' bedeutet, dass keine
	Resource-Datei eingelesen werden soll.

--version
	Gibt die Versionsummer aus. 
Durchsuche die Quelldateien rekursiv, und überspringe Patches und Quilt-
Metainformation. Wenn kein Dateiname angegeben wird, wird der gesamte
Quellbaum durchsucht. Siehe die grep(1) Manual Page zu Optionen.

-h	Gib diese Hilfsmeldung aus. Die grep -h - Option kann nach einem
	Doppelstrick (--) angegeben werden. Suchausdrücke, die mit einem Strich
	beginnen, können nach einem weiteren Doppelstrich (--) angegeben werden.
 
Importiere externe Patches. Die Patches werden nach dem momentan obersten
Patch eingefügt, und können dann mit dem push-Befehl angewandt werden.

-p num
	Die Anzahl der Komponenten im Pfadnamen, die beim Anwenden des Patches
	entfernt werden sollen (Standard=1).

-R
	Patch umgekehrt anwenden.

-P patch
	Patch-Dateiname, den Quilt verwenden soll. Diese Option kann nur beim
	Import eines einzelnen Patches angegeben werden.

-f	Überschreibe/aktualisiere existierende Patches.

-d {o|a|n}
	Erhalte beim Überschreiben von Patches den alten (o), alle (a), oder den
	neuen (n) Patch-Header. Wenn beide Patches Header enthalten, muss diese
	Option angegeben werden. Diese Option ist nur in Kombination mit -f wirksam.
 
Integriert den Patch von der Standardeingabe in den obersten Patch:
Stellt zuerst sicher, dass alle Dateien, die verändert werden, im
obersten Patch enthalten sind, und wendet dann den neuen Patch
mit der angegebenen Anzahl an Strip-Ebenen an (Standardwert = 1).

-r	Patch vekehrt herum anwenden.

-q	Wenige Meldungen ausgeben.

-f	Anwenden erzwingen, selbst wenn dabei Fehler auftreten. Wenn -q nicht
	angegeben wird der Patch interaktiv angewandt, und das Patch-Utility
	kann fragen stellen.

-p strip-ebenen
	Die Anzahl der Komponenten im Pfadnamen, die beim Anwenden des Patches
	entfernt werden sollen.
 
Bitte entfernen Sie alle Patches mit \`quilt pop -a' der quilt-Version, die zur Erzeugung des Arbeitsverzeichnis verwendet wurden, oder entfernen Sie das Verzeichnis %s, und wenden Sie die Patches neu an.\n 
Gibt eine Liste der angewandten Patches aus, oder eine Liste aller Patches
vom Anfang der series-Datei bis zum angegebenen Patch.
 
Gint eine Liste der Patches aus, die momentan nicht angewandt sind, bzw.
eine Liste der Patches, die dem angegebenen Patch folgen.
 
Erzeuge ein Listing der angegebenen Datei das anzeigt, welche
Patches welche Zeilen verändern. Nur angewandte Patches werden
angezeigt.

-P patch
	Nur bis zum angegebenen Patch anstatt bis zum obersten Patch
	nach Änderungen suchen.
 
Zeige den Header des obersten oder angegebenen Patches an, oder verändere ihn.

-a, -r, -e
	Füge Text von der Standardeingabe an den Header an (-a), ersetze den Header
	mit der Standardeingabe, oder editiere den Header in \$EDITOR (%s). Wenn keine
	dieser Optionen angegeben ist, gib den Header aus.

--strip-diffstat
	Entferne diffstat-Ergebnisse vom Header.

--strip-trailing-whitespace
	Entferne Whitespace an Zeilenenden im Header.

--backup
	Erzeuge eine Sicherungskopie von patch als patch~.
 
Gibt eine Liste der Dateien aus, die der oberste oder angegebene Patch
beinhaltet.

-a	Zeigt alle Dateien in allen angewandten Patches an.

-l	Gibt auch die Patchnamen mit aus.

-v	Ausführlichere, benutzerfreundliche Ausgabe.

--combine patch
	Erzeige eine Liste für alle Patches zwischen diesem und dem obersten
	oder angegebenen Patch am Stack. Der Patchname \`-'
	entspricht dem ersten angewandten Patch.

 
Gibt den Namen des nächsten Patches nach dem obersten oder angegebenen
Patch in der series-Datei aus.
 
Gibt den Namen des Patches vor dem obersten oder angegebenen
Patch in der series-Datei aus.
 
Gibt den Namen des obersten Patches auf dem Stapel aus.
 
Frischt den obersten oder angegebenen Patch auf. Dokumentation in der
Patch-Datei, die vor dem eigentlichen Patch steht, bleibt dabei
erhalten.

Es können beliebige angewandte Patches aktualisiert werden. Wenn
Patches, die nach dem angegebenen Patch angewandt sind, dieselben
Dateien verändern, die auch dieser Patch verändert, bricht dieses Script
normalerweise ab. Mit der Option -f kann das Aktalisieren trotzdem
erzwungen werden. Dann wird für jede Datei, die später noch verändert
wurde, eine Warnung ausgegeben, und nur Änderungen in Dateien, die
danach nicht von anderen Patches weiter verändert werden, werden beim
Aktalisieren berücksichtigt.

-p n	Erzeuge einen -p n Patch (n=0 oder n=1 werden unterstützt).

-p ab	Erzeuge einen -p1-artigen Patch, verwende aber a/datei und
	b/datei als den ursprünglichen und neuen Dateinamen anstelle von
	dir.orig/datei und dir/datei.

-u, -U anzahl, -c, -C anzahl
	Erzeuge ein Unified Diff (-u, -U) mit anzahl Kontextzeilen. Erzeuge
	ein Context Diff (-c, -C) mit anzahl Kontextzeilen. Die Anzahl der
	Kontextzeilen ist 3, wenn nicht anders angegeben.

-z[neuer_name]
	Erzeuge einen neuen Patch mit den Änderungen, statt den obersten
	Patch zu aktualisieren. Wenn kein neuer Name angegeben wird, wird
	\`-2' an den Namen angehängt, usw (siehe das fork-Kommando).

--no-timestamps
	Keine Zeitstempel in Patches angeben.

--no-index
	Erzeuge keine \`Index:'-Zeilen

--diffstat
	Füge dem Patch-Kopf einen diffstat-Abschnitt hinzu, oder ersetzte den
	bestehenden Abschnitt.

-f	Erzwinge das Aktalisieren eines Patches, der sich nicht an oberster
	Position befindet.

--no-timestamps
	Keine Zeitstempel in Patches angeben (wie QUILT_DIFF_NO_TIMESTAMPS in~/.quiltrc).

--backup
	Erzeuge ein Backup der alten Version von patch als patch~

--sort	Sortiere Dateien im Patch nach ihrem namen, statt die ursprüngliche
	Reihenfolge zu erhalten.

--strip-trailing-whitespace
	Entferne Whitespace an Zeilenenden.
 
Entferne Patches vom Stapel der angewandten Patches. Es kann eine Anzahl
von Patches, die entfernt werden soll, oder der Name eines Patches
angegeben werden. Wenn ein Name angegeben wird, werden alle Patches über
dem angegebenen Patch entfernt. Wenn weder ein Patchname noch eine Nummer
angegeben wird, wird der oberste Patch entfernt.

-a	Alle angewandten Patches entfernen.

-f	Erzwungenes Entfernen. Der Zustand vor dem Anwenden das Patches wird
	über die Sicherungsdateien wiederhergestellt.

-R	 Überprüfe immer, ob sich Patches vollständig entfernen lassen;
	nicht auf Datei-Zeitspempel verlassen.

-q	Wenige Meldungen ausgeben.

-v	Viele Meldungen ausgeben.
 
Löscht den obersten oder angegebenen Patch aus der series-Datei. Falls
dieser Patch angewandt ist, entfernt quilt ihn zuerst. (Momentan kann 
nur der oberste Patch entfernt werden.)

-n	Lösche den nächsten (dem obersten folgenden) Patch statt des obersten
	oder angegebenen.

-r	Entferne den Patch auch aus dem patches-Verzeichnis.

--backup
	Benenne den Patch auf patch~, anstatt ihn zu löschen.
	Hat nur in Kompination mit -r eine Wirkung.
 
Benennt den obersten oder angegebenen Patch um.

-P patch
	Patch, der umbenannt werden soll.
 
Erzeuge einen Snapshot des aktuellen Zustands des Quellbaums. Danach kann
der Quellbaum auf die üblichen Arten verändert werden, inklusive dem
Hinzufügen und Entfernen von Patches. Ein Patch zwischen dem Quellbaum
zum Zeitpunkt des Snapshots und dem aktuellen Zustand kann mit
\`quilt diff --snapshot' erzeugt werden.

-d	Entferne lediglich den aktuellen Snapshot.
 
Aktualisiere die Metadaten in einem Arbeitsverzeichnis von einer älteren Version
von quilt zur aktuellen. Dieses Kommando wird nur benötigt, wenn sich das
Format der Metadaten verändert hat, und das Arbeitsverzeichnis noch alte
Metadaten enthält. In diesem Fall fordert quilt dazu auf, \`quilt upgrade'
auszuführen.
             quilt --version %s: Ich bin verwirrt.
 Text an Header von Patch %s angefügt\n Patch %s angewandt (erzwungen, muss aktualisiert werden (Refresh))\n Wende Patch %s an\n Kann nur den obersten Patch mit -z aktualisieren\n Kann symbolische Verknüpfung %s nicht hinzufügen\n Kann kein Diff mit -p%s erzeugen, bitte -p0, -p1 oder -pab verwenden.\n Kann --strip-trailing-whitespace nicht für Patches verwenden, die Dateien enthalten, die danach von anderen Patches weiter verändert werden.\n Änderungen an %s in Patch %s zurückgenommen\n Vorhandene Befehle: Konvertierung fehlgeschlagen\n Konvertiere Metadaten in Version %s\n Konnte die Envelope-Adresse nicht feststellen. Bitte verwenden Sie --sender. Zustelladresse `%s' ist ungültig
 Diff fehlgeschlagen, Abbruch.\n Verzeichnis %s existiert\n Anzeigename `%s' enthält eine unvollständige Klammerung
 Konnte Datei %s nicht sichern\n Konnte Datei %s nicht sichern\n Konnte Dateien nicht in temporäres Verzeichnis kopieren\n Konnte Patch %s nicht erzeugen\n Konnte Patch %s nicht importieren\n Konnte Patch %s nicht in die series-Datei einfügen\n Konnte temporäre Dateien nicht patchen\n Konnte Datei %s aus Patch %s nicht entfernen\n Konnte Patch %s nicht entfernen\n Konnte Patch %s nicht entfernen\n Konnte Änderungen an %s in Patch %s nicht zurücknehmen\n Datei %s zu Patch %s hinzugefügt\n Datei %s existiert nicht\n Datei %s existiert\n Datei %s ist bereits in Patch $patch\n Die Datei %s befindet sich unter dem Verzeichnis %s\n Datei %s wird nicht verändert.\n Datei %s ist nicht in Patch %s\n Datei %s ist unverändert\n Datei %s ist möglicherweise defekt\n Datei %s wird von Patch %s verändert\n Datei %s nicht gefunden\n Datei %s aus Patch %s entfernt\n series-Datei vollständig angewandt, endet in Patch %s\n Neue Version von %s erstellt als %s\n Fehler beim Aufspalten von %s auf %s\n Importiere Patch %s (abgelegt als %s)\n Importiere patch %s\n Unterbrechung durch Benutzer; Patch %s wurde nicht angewandt.\n Die Einleitung hat keine Subject-Kopfzeile (gespeichert als %s)\n Die Einleitung hat keine Subject-Kopfzeile\n Einleitung gespeichert als %s\n Später angewandte Patches verändern Dateien von %s. Aktalisieren mit -f erzwingen.\n Kein Patch %s\n Kein Patch entfernt\n Keine Patches angewandt\n Keine Patches in der series-Datei\n Patch %s ist leer\n Jetzt in Patch %s\n Die Option \`-P' kann nur beim Importieren eines einzelnen Patches verwendet werden\n Die Optionen \`--combine', \`--snapshot', und \`-z' können nicht kombiniert werden.\n Patch %s existiert bereits in der series-Datei\n Patch %s scheint leer zu sein; wird entfernt\n Patch %s scheint leer zu sein; angewandt\n Patch %s kann verkehrt angewandt werden\n Patch %s lässt sich nicht anwenden (erzwingen mit -f)\n Patch %s existiert nicht; wende leeren patch an\n Patch %s existiert nicht\n Patch %s kann nicht entfernt werden (Patch aktualisieren oder entfernen erzwingen mit -f)\n Patch %s existiert bereits, bitte einen anderen Namen wählen\n Patch %s existiert bereits, bitte neuen Namen wählen\n Patch %s existiert bereits\n Patch %s existiert bereits. Ersetzen mit -f.\n Patch %s ist angewandt\n Patch %s ist momentan angewandt\n Patch %s ist nicht angewandt\n Patch %s ist nicht in der series-Datei\n Der oberste Patch ist jetzt %s\n Patch %s ist unverändert\n Patch %s muss zuerst aktualisiert werden (Refresh).\n Patch %s ist nicht vor Patch %s angewandt\n Patch %s auf %s umbenannt\n Die Patch-Header unterscheiden sich:\n Die Patches %s haben die selben Subject-Kopfzeilen.\n Bitte verwenden Sie die Option -d {o|a|n} um anzugeben, welche Patch-Header erhalten bleiben sollen.\n Patch %s aktualisiert\n Entferne Patch %s\n Entferne patch %s\n Entferne abschliessende Leerzeichen in Zeile %s von %s
 Entferne abschliessende Leerzeichen in den Zeilen %s von %s
 Umbenennen von %s auf %s: %s
 Fehler beim Umbenennen von Patch %s auf %s\n Header von Patch %s ersetzt\n Ersetze Patch %s durch neuere Version\n Aufruf: %s [-p num] [-n] [patch]
 Der %%prep-Abschnitt von %s ist fehlgeschlagen; die Ergebnisse sind möglicherweise unvollständig\n Die Option -v zeigt die Ausgaben von rpm an\n Die Metadaten in $QUILT_PC/ sind bereits in Format Version $DB_VERSION; nichts zu tun\n Die quilt-Metadaten in diesem Arbeitsverzeichnis haben Version $version, aber diese Version von quilt kann nur mit Metadaten in den Versionen $DB_VERSION und darunter umgehen. Bitte entfernen Sie vor dem Downgrade von quilt alle Patches mit der Version von quilt, die zur Erstellung des Arbeitsverzeichnisses verwendet wurde.\n Der oberste Patch %s muss zuerst aktualisiert werden (Refresh).\n Das Arbeitsverzeichnis wurde von einer älteren Version von quilt erstellt. Bitte führen Sie \`quilt upgrade' aus.\n Konnte keine Subject-Kopfzeile aus %s extrahieren\n Entpacke Archiv %s\n Verwendung: quilt [--trace[=verbose]] [--quiltrc=XX] befehl [-h] ... Verwendung: quilt add [-P patch] {datei} ...\n Verwendung: quilt annotate [-P patch] {datei}\n Verwendung: quilt applied [patch]\n Verwendung: quilt delete [-r] [--backup] [patch|-n]\n Verwendung: quilt edit datei ...\n Verwendung: quilt files [-v] [-a] [-l] [--combine patch] [patch]\n Verwendung: quilt fold [-R] [-q] [-f] [-p strip-ebenen]\n Verwendung: quilt fork [neuer_name]\n Verwendung: quilt graph [--all] [--reduce] [--lines[=num]] [--edge-labels=files] [-T ps] [patch]\n Verwendung: quilt grep [-h|options] {suchausdruck}\n Verwendung: quilt header [-a|-r|-e] [--backup] [--strip-diffstat] [--strip-trailing-whitespace] [patch]\n Verwendung: quilt import [-p num] [-R] [-P patch] [-f] [-d {o|a|n}] [patchdatei] ...\n Verwendung: quilt new [-p n|-p ab] {patchname}\n Verwendung: quilt next [patch]\n Verwendung: quilt pop [-afRqv] [num|patch]\n Verwendung: quilt previous [patch]\n Verwendung: quilt push [-afqv] [--merge[=merge|diff3]] [--leave-rejects] [--color[=always|auto|never]] [num|patch]\n Verwendung: quilt refresh [-p n|-p ab] [-u|-U num|-c|-C num] [-z[new_name]] [-f] [--no-timestamps] [--no-index] [--diffstat] [--sort] [--backup] [--strip-trailing-whitespace] [patch]\n Verwendung: quilt remove [-P patch] {datei} ...\n Verwendung: quilt rename [-P patch] neuer_name\n Verwendung: quilt revert [-P patch] {datei} ...\n Verwendung: quilt setup [-d pfad-präfix] [-v] [--sourcedir verzeichnis] [--fuzz=N] {spec-datei|series-datei}\n Verwendung: quilt snapshot [-d]\n Verwendung: quilt top\n Verwendung: quilt unapplied [patch]\n Verwendung: quilt upgrade\n Warnung: später angewandte Patches verändern Dateien von %s\n Warnung: abschliessende Leerzeichen in Zeile %s von %s
 Warnung: abschliessende Leerzeichen in den Zeilen %s von %s
 