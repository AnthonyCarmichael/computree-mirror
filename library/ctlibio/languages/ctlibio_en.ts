<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="en_US">
<context>
    <name>CT_Reader_ASCRGB</name>
    <message>
        <location filename="../readers/ct_reader_ascrgb.cpp" line="19"/>
        <source>Fichiers de points ASCII (XYZRGB, sans entête, RGB [0;1])</source>
        <translation>ASCII point files (XYZRGB, no header, RGB [0;1])</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ascrgb.cpp" line="21"/>
        <source>Charge un fichier de points au format ASCII, sans entête, ordonné, avec les champs suivants :&lt;br&gt;- X  : Coordonnée X&lt;br&gt;- Y  : Coordonnée Y&lt;br&gt;- Z  : Coordonnée Z&lt;br&gt;- R  : Composante rouge, valeur entre 0 et 1 (optionnel)&lt;br&gt;- V  : Composante verte, valeur entre 0 et 1 (optionnel)&lt;br&gt;- B  : Composante Bleue, valeur entre 0 et 1 (optionnel)&lt;br&gt;</source>
        <translation>Loads a point file in ASCII format, without header, ordered, with the following fields:&lt;br&gt;- X: X coordinate&lt;br&gt;- Y: Y coordinate&lt;br&gt;- Z: Z coordinate&lt;br&gt;- R: Red component, value between 0 and 1 (optional)&lt;br&gt;- V: Green component, value between 0 and 1 (optional)&lt;br&gt;- B: Blue component, value between 0 and 1 (optional)&lt;br&gt;</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ascrgb.cpp" line="39"/>
        <source>Points, fichier ASCII (XYZRGB, sans entête, RGB [0;1])</source>
        <translation>Points, ASCII file (XYZRGB, no header, RGB [0;1])</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ascrgb.cpp" line="131"/>
        <source>Le fichier %1 n&apos;a pas le bon format (colonnes manquantes).</source>
        <translation>The %1 file has the wrong format (missing columns).</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ascrgb.cpp" line="133"/>
        <source>Le fichier %1 est vide.</source>
        <translation>The %1 file is empty.</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ascrgb.cpp" line="141"/>
        <source>Scène</source>
        <translation>Scene</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ascrgb.cpp" line="142"/>
        <source>Attribut de points (couleurs)</source>
        <translation>Point attribute (colours)</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ascrgb.cpp" line="226"/>
        <source>Le fichier %1 n&apos;est pas accessible.</source>
        <translation>The file %1 is not accessible.</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ascrgb.cpp" line="229"/>
        <source>Le fichier %1 n&apos;existe pas.</source>
        <translation>The file %1 does not exist.</translation>
    </message>
</context>
<context>
    <name>CT_Reader_AsciiGrid3D</name>
    <message>
        <location filename="../readers/ct_reader_asciigrid3d.cpp" line="31"/>
        <source>Fichiers grille 3D</source>
        <translation>3D grid files</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_asciigrid3d.cpp" line="33"/>
        <source>Chargement d&apos;une grille 3D depuis un fichier ASCII (format inspiré du format raster ESRI GRID).</source>
        <translation>Loading a 3D grid from an ASCII file (format inspired by the ESRI GRID raster format).</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_asciigrid3d.cpp" line="43"/>
        <source>Grille 3D, Fichiers ascii GRD3D</source>
        <translation>3D grid, GRD3D ascii files</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_asciigrid3d.cpp" line="99"/>
        <source>Grille 3D</source>
        <translation>3D grid</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_asciigrid3d.cpp" line="264"/>
        <source>Read header of file &quot;%1&quot;</source>
        <translation>Read header of file &quot;%1&quot;</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_asciigrid3d.cpp" line="299"/>
        <source>Data type &quot;%1&quot; founded in header</source>
        <translation>Data type &quot;%1&quot; founded in header</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_asciigrid3d.cpp" line="301"/>
        <source>Unable to read the data type &quot;%1&quot; founded at line %2. Create a grid of &quot;float&quot; by default.</source>
        <translation>Unable to read the data type &quot;%1&quot; founded at line %2. Create a grid of type &quot;float&quot; by default.</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_asciigrid3d.cpp" line="313"/>
        <source>Data type defined as &quot;%1&quot; (by intuition). If you want to force the data type you must insert the string &quot;datatype XXXX&quot; at line %2 (line after the NODATA_value). XXXX must be replaced by &quot;%3&quot; for int, &quot;%4&quot; for float, &quot;%5&quot; for bool, etc...</source>
        <translation>Data type defined as &quot;%1&quot; (by intuition). If you want to force the data type you must insert the string &quot;datatype XXXX&quot; at line %2 (line after the NODATA_value). XXXX must be replaced by &quot;%3&quot; for int, &quot;%4&quot; for float, &quot;%5&quot; for bool, etc...</translation>
    </message>
</context>
<context>
    <name>CT_Reader_CTIndex</name>
    <message>
        <location filename="../readers/ct_reader_ctindex.cpp" line="18"/>
        <source>Fichiers d&apos;indexation de points CTI</source>
        <translation>CTI point index files</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ctindex.cpp" line="19"/>
        <source>Le format CTI indexe des listes de points depuis une liste de fichiers de référence</source>
        <translation>The CTI format indexes lists of points from a list of reference files</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ctindex.cpp" line="44"/>
        <source>Index de points, Fichier CTI</source>
        <translation>Point index, CTI file</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ctindex.cpp" line="214"/>
        <location filename="../readers/ct_reader_ctindex.cpp" line="217"/>
        <location filename="../readers/ct_reader_ctindex.cpp" line="220"/>
        <source>Emprise Complète</source>
        <translation>Full extent</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ctindex.cpp" line="225"/>
        <location filename="../readers/ct_reader_ctindex.cpp" line="228"/>
        <location filename="../readers/ct_reader_ctindex.cpp" line="231"/>
        <source>Emprise Réduite</source>
        <translation>Reduced extent</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ctindex.cpp" line="243"/>
        <source>Impossible de lire l&apos;en-tête du fichier %1</source>
        <translation>Unable to read file header %1</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ctindex.cpp" line="342"/>
        <source>Reader for %1 wasn&apos;t created properly.</source>
        <translation>Reader for %1 wasn&apos;t created properly.</translation>
    </message>
</context>
<context>
    <name>CT_Reader_GDAL</name>
    <message>
        <location filename="../readers/ct_reader_gdal.cpp" line="123"/>
        <source>Layer %1</source>
        <translation>Layer %1</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_gdal.cpp" line="255"/>
        <source>Points</source>
        <translation>Points</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_gdal.cpp" line="267"/>
        <source>Polygones</source>
        <translation>Polygons</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_gdal.cpp" line="279"/>
        <source>Polylignes</source>
        <translation>Polylines</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_gdal.cpp" line="311"/>
        <source>Impossible de charger des éléments du type : </source>
        <translation>Unable to load items of type : </translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_gdal.cpp" line="899"/>
        <source>Reader GDAL de type : %1</source>
        <translation>Reader GDAL type: %1</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_gdal.cpp" line="899"/>
        <source>Inconnu</source>
        <translation>Unknown</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_gdal.cpp" line="905"/>
        <source>Pour plus de détails voir : http://www.gdal.org/formats_list.html</source>
        <translation>For more details see: http://www.gdal.org/formats_list.html</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_gdal.cpp" line="910"/>
        <source>Pour plus de détails voir : http://www.gdal.org/ogr_formats.html</source>
        <translation>For more details see: http://www.gdal.org/ogr_formats.html</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_gdal.cpp" line="914"/>
        <source>Extension : </source>
        <translation>Extension : </translation>
    </message>
</context>
<context>
    <name>CT_Reader_IDXYZ</name>
    <message>
        <location filename="../readers/ct_reader_idxyz.cpp" line="15"/>
        <source>Fichiers de points ASCII (XYZRGB, sans entête, RGB [0;1])</source>
        <translation>ASCII point files (XYZRGB, no header, RGB [0;1])</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_idxyz.cpp" line="17"/>
        <source>Charge un fichier de clusters de points au format ASCII, avec les champs suivants :&lt;br&gt;- ID : ID du cluster&lt;br&gt;- X  : Coordonnée X&lt;br&gt;- Y  : Coordonnée Y&lt;br&gt;- Z  : Coordonnée Z&lt;br&gt;</source>
        <translation>Loads a point cluster file in ASCII format, with the following fields:&lt;br&gt;- ID: Cluster ID&lt;br&gt;- X: X coordinate&lt;br&gt;- Y: Y coordinate&lt;br&gt;- Z: Z coordinate&lt;br&gt;</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_idxyz.cpp" line="30"/>
        <source>Clusters de Points, fichier ASCII (ID, X, Y, Z)</source>
        <translation>Point clusters, ASCII file (ID, X, Y, Z)</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_idxyz.cpp" line="45"/>
        <source>Le fichier %1 n&apos;a pas le bon format (colonnes manquantes).</source>
        <translation>The %1 file has the wrong format (missing columns).</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_idxyz.cpp" line="48"/>
        <source>Le fichier %1 est vide.</source>
        <translation>The %1 file is empty.</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_idxyz.cpp" line="57"/>
        <source>Scène complète</source>
        <translation>Full scene</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_idxyz.cpp" line="58"/>
        <source>Groupe</source>
        <translation>Group</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_idxyz.cpp" line="59"/>
        <source>Scène ID</source>
        <translation>Scene ID</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_idxyz.cpp" line="176"/>
        <source>Le fichier %1 n&apos;est pas accessible.</source>
        <translation>The file %1 is not accessible.</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_idxyz.cpp" line="179"/>
        <source>Le fichier %1 n&apos;existe pas.</source>
        <translation>The file %1 does not exist.</translation>
    </message>
</context>
<context>
    <name>CT_Reader_LArchitect_Grid</name>
    <message>
        <location filename="../readers/ct_reader_larchitect_grid.cpp" line="30"/>
        <source>Fichiers de grilles 3D LArchitect</source>
        <translation>LArchitect 3D grid files</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_larchitect_grid.cpp" line="31"/>
        <source>Charge des grilles 3D depuis un fichier au format LArchitect</source>
        <translation>Loading 3D grids from a file in LArchitect format</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_larchitect_grid.cpp" line="42"/>
        <source>Grilles 3D, format LArchitect</source>
        <translation>3D grids, LArchitect format</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_larchitect_grid.cpp" line="67"/>
        <source>Error when read header of the file %1</source>
        <translation>Error when reading header of the file %1</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_larchitect_grid.cpp" line="80"/>
        <source>Wood surface</source>
        <translation>Wood surface</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_larchitect_grid.cpp" line="81"/>
        <source>Leaf surface</source>
        <translation>Leaf surface</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_larchitect_grid.cpp" line="82"/>
        <source>Wood volume</source>
        <translation>Wood volume</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_larchitect_grid.cpp" line="83"/>
        <source>Leaf volume</source>
        <translation>Leaf volume</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_larchitect_grid.cpp" line="84"/>
        <source>Total surface</source>
        <translation>Total surface</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_larchitect_grid.cpp" line="85"/>
        <source>Total volume</source>
        <translation>Total volume</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_larchitect_grid.cpp" line="155"/>
        <source>Pas d&apos;index bois dans le fichier</source>
        <translation>No wood index in the file</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_larchitect_grid.cpp" line="156"/>
        <source>Pas d&apos;index feuille dans le fichier</source>
        <translation>No leaf index in the file</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_larchitect_grid.cpp" line="220"/>
        <source>Indice hors grille</source>
        <translation>Off-grid index</translation>
    </message>
</context>
<context>
    <name>CT_Reader_OBJ</name>
    <message>
        <location filename="../readers/ct_reader_obj.cpp" line="16"/>
        <source>Fichiers de géométrie 3D .obj</source>
        <translation>3D geometry files .obj</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_obj.cpp" line="18"/>
        <source>Charge un maillage ou un nuage de points depuis un fichier au format OBJ (Objet 3D)</source>
        <translation>Loads a mesh or a point cloud from a file in OBJ (3D Object) format</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_obj.cpp" line="29"/>
        <source>Mesh ou Points, Fichier OBJ</source>
        <translation>Mesh or Points, OBJ File</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_obj.cpp" line="55"/>
        <source>Rechercher les demis arêtes ? (accélère le chargement si non coché)</source>
        <translation>Search for half-edges (speeds up loading if not checked)</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_obj.cpp" line="56"/>
        <source>Forcer le chargement en tant que nuage de points</source>
        <translation>Force loading as a point cloud</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_obj.cpp" line="93"/>
        <source>Scene</source>
        <translation>Scene</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_obj.cpp" line="95"/>
        <source>Mesh Model</source>
        <translation>Mesh Model</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_obj.cpp" line="321"/>
        <source>%1 vertex et %2 face(s) à charger pour le fichier %3</source>
        <translation>%1 vertex and %2 face(s) to be loaded for file %3</translation>
    </message>
</context>
<context>
    <name>CT_Reader_OPF</name>
    <message>
        <location filename="../readers/ct_reader_opf.cpp" line="21"/>
        <source>Fichiers AmapStudio .opf</source>
        <translation>AmapStudio .opf files</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_opf.cpp" line="23"/>
        <source>Charge un fichier décrivant l&apos;architecture de végétaux au format OPF, créé par le logiciel AMAPStudio.&lt;br&gt;http://amapstudio.cirad.fr</source>
        <translation>Loads a file describing the plant architecture in OPF format, created by the AMAPStudio software.&lt;br&gt;https://amapstudio.cirad.fr</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_opf.cpp" line="46"/>
        <source>Fichier AmapStudio - OPF</source>
        <translation>AmapStudio file - OPF</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_opf.cpp" line="220"/>
        <source>No types found in %1</source>
        <translation>No types found in %1</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_opf.cpp" line="229"/>
        <source>Topologie</source>
        <translation>Topology</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_opf.cpp" line="263"/>
        <source>Mesh</source>
        <translation>Mesh</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_opf.cpp" line="394"/>
        <source>Charger le modèle 3D ? (lent si activé)</source>
        <translation>Load 3D model (slow if enabled)</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_opf.cpp" line="394"/>
        <source>Ralentit les performances lors du chargement des mesh</source>
        <translation>Slows down performance when loading meshes</translation>
    </message>
</context>
<context>
    <name>CT_Reader_PLY</name>
    <message>
        <location filename="../readers/ct_reader_ply.cpp" line="43"/>
        <source>Fichiers de géométrie 3D .ply</source>
        <translation>3D geometry files .ply</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ply.cpp" line="45"/>
        <source>Charge un nuage de points depuis un fichier au format PLY (Objet 3D)</source>
        <translation>Loads a point cloud from a PLY (3D object) file</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ply.cpp" line="62"/>
        <source>Points, Fichier PLY</source>
        <translation>Points, PLY File</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ply.cpp" line="71"/>
        <source>L&apos;en-tête du fichier &quot;%1&quot; n&apos;est pas formé correctement.</source>
        <translation>The header of file &quot;%1&quot; is not formed correctly.</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ply.cpp" line="216"/>
        <source>Scene</source>
        <translation>Scene</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ply.cpp" line="229"/>
        <source>Color %1</source>
        <translation>Color %1</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ply.cpp" line="238"/>
        <source>Normal %1</source>
        <translation>Normal %1</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ply.cpp" line="247"/>
        <source>Scalar %1</source>
        <translation>Scalar %1</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ply.cpp" line="353"/>
        <source>ATTENTION : les filtres ne sont pas pris en charges pour le format PLY pour le moment. Tous les points seront chargés.</source>
        <translation>ATTENTION: Filters are not supported for the PLY format at the moment. All points will be loaded.</translation>
    </message>
</context>
<context>
    <name>CT_Reader_PTX</name>
    <message>
        <location filename="../readers/ct_reader_ptx.cpp" line="20"/>
        <source>Fichiers de points .ptx</source>
        <translation>Point files .ptx</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ptx.cpp" line="22"/>
        <source>Chargement de points depuis un fichier format ascii PTX</source>
        <translation>Loading points from an ascii PTX file</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ptx.cpp" line="32"/>
        <source>Points, Fichier PTX</source>
        <translation>Points, PTX file</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ptx.cpp" line="65"/>
        <source>Appliquer la matrice de transformation</source>
        <translation>Apply the transformation matrix</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ptx.cpp" line="172"/>
        <source>Scène</source>
        <translation>Scene</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ptx.cpp" line="173"/>
        <source>Intensité</source>
        <translation>Intensity</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ptx.cpp" line="174"/>
        <source>RGB</source>
        <translation>RGB</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ptx.cpp" line="175"/>
        <source>Matrice de transformation</source>
        <translation>Transformation matrix</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_ptx.cpp" line="176"/>
        <source>Scanner</source>
        <translation>Scanner</translation>
    </message>
</context>
<context>
    <name>CT_Reader_Points_ASCII</name>
    <message>
        <location filename="../readers/ct_reader_points_ascii.cpp" line="55"/>
        <source>Fichiers ascii</source>
        <translation>Ascii files</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_points_ascii.cpp" line="57"/>
        <source>Chargement d&apos;un fichier de points au format ASCII.&lt;br&gt;L&apos;import est configurable, le fichier devant contenir les champs suivants :&lt;br&gt;- X      : Coordonnée X du points&lt;br&gt;- Y      : Coordonnée Y du point&lt;br&gt;- Z      : Coordonnée Y du point&lt;br&gt;&lt;br&gt;De plus les champs suivants peuvent être fournis mais sont optionnels :&lt;br&gt;- Intensité      : Intensité du point&lt;br&gt;- Rouge          : Composante rouge du point&lt;br&gt;- Vert           : Composante verte du point&lt;br&gt;- Bleu           : Composante bleue du point&lt;br&gt;- Normale X      : Coordonnée Y de la normale au point&lt;br&gt;- Normale Y      : Coordonnée Y de la normale au point&lt;br&gt;- Normale Z      : Coordonnée Y de la normale au point&lt;br&gt;</source>
        <translation>Loading a point file in ASCII format.&lt;br&gt;The import is configurable, the file must contain the following fields:&lt;br&gt;- X: X coordinate of the point&lt;br&gt;- Y: Y coordinate of the point&lt;br&gt;- Z: Y coordinate of the point&lt;br&gt;&lt;br&gt;In addition the following fields can be provided but are optional:&lt;br&gt;- Intensity: Intensity of the point&lt;br&gt;- Red: Red component of the point&lt;br&gt;- Green: Green component of the point&lt;br&gt;- Blue: Blue component of the point&lt;br&gt;- X-normal: Y-coordinate of the point normal&lt;br&gt;- Y-normal: Y-coordinate of the point normal&lt;br&gt;- Z-normal: Y-coordinate of the point normal&lt;br&gt;</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_points_ascii.cpp" line="95"/>
        <source>Nuage de points, Fichiers ASCII (paramétrable)</source>
        <translation>Point cloud, ASCII files (configurable)</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_points_ascii.cpp" line="441"/>
        <source>Scène(s)</source>
        <translation>Scene(s)</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_points_ascii.cpp" line="446"/>
        <source>Intensités</source>
        <translation>Intensities</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_points_ascii.cpp" line="451"/>
        <source>Couleurs</source>
        <translation>Colours</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_points_ascii.cpp" line="456"/>
        <source>Normales</source>
        <translation>Normals</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_points_ascii.cpp" line="518"/>
        <source>Error loading at line %1: missing columns.</source>
        <translation>Error loading at line %1: missing columns.</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_points_ascii.cpp" line="522"/>
        <source>Error loading point at line %1</source>
        <translation>Error loading point at line %1</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_points_ascii.cpp" line="528"/>
        <source>Error loading intensity at line %1</source>
        <translation>Error loading intensity at line %1</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_points_ascii.cpp" line="529"/>
        <source>Error loading color at line %1</source>
        <translation>Error loading color at line %1</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_points_ascii.cpp" line="530"/>
        <source>Error loading normal at line %1</source>
        <translation>Error loading normal at line %1</translation>
    </message>
</context>
<context>
    <name>CT_Reader_TRJ</name>
    <message>
        <location filename="../readers/ct_reader_trj.cpp" line="14"/>
        <source>Trajectoire TerraScan .trj</source>
        <translation>TerraScan trajectory .trj</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_trj.cpp" line="15"/>
        <source>Chargement de trajectoires à partir du format binaire TerraScan .trj</source>
        <translation>Loading trajectories from the TerraScan .trj binary format</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_trj.cpp" line="24"/>
        <source>Trajectoire TerraScan, Fichier TJR</source>
        <translation>TerraScan trajectory, TJR file</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_trj.cpp" line="117"/>
        <source>Trajectoire</source>
        <translation>Trajectory</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_trj.cpp" line="126"/>
        <source>Impossible de lire l&apos;en-tête du fichier %1</source>
        <translation>Unable to read file header %1</translation>
    </message>
</context>
<context>
    <name>CT_Reader_TerraScanPrj</name>
    <message>
        <location filename="../readers/ct_reader_terrascanprj.cpp" line="10"/>
        <source>Fichier TerraScan PRJ</source>
        <translation>TerraScan PRJ file</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_terrascanprj.cpp" line="11"/>
        <source>Charge un fichier d&apos;emprises de dalles (LIDAR), au format TerraScan PRJ</source>
        <translation>Loads a footprint file (LIDAR), in TerraScan PRJ format</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_terrascanprj.cpp" line="20"/>
        <source>Fichier TerraScan - PRJ</source>
        <translation>TerraScan file - PRJ</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_terrascanprj.cpp" line="50"/>
        <source>Emprise de la dalle</source>
        <translation>Tile footprint</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_terrascanprj.cpp" line="51"/>
        <source>Fichier de la dalle</source>
        <translation>Tile file</translation>
    </message>
</context>
<context>
    <name>CT_Reader_Trajectory</name>
    <message>
        <location filename="../readers/ct_reader_trajectory.cpp" line="27"/>
        <source>Fichiers ascii</source>
        <translation>Ascii files</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_trajectory.cpp" line="29"/>
        <source>Chargement d&apos;un fichier de trajectoire au format ASCII.&lt;br&gt;L&apos;import est configurable, le fichier devant contenir les champs suivants :&lt;br&gt;- X          : Coordonnée X du points&lt;br&gt;- Y          : Coordonnée Y du point&lt;br&gt;- Z          : Coordonnée Y du point&lt;br&gt;&lt;br&gt;- GPSTime    : Temps GPS du point&lt;br&gt;</source>
        <translation>Loading a trajectory file in ASCII format.&lt;br&gt;The import is configurable, the file must contain the following fields:&lt;br&gt;- X: X coordinate of the point&lt;br&gt;- Y: Y coordinate of the point&lt;br&gt;- Z: Y coordinate of the point&lt;br&gt;&lt;br&gt;- GPSTime: GPS time of the point&lt;br&gt;</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_trajectory.cpp" line="53"/>
        <source>Trajectoire, Fichiers ASCII</source>
        <translation>Trajectory, ASCII files</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_trajectory.cpp" line="257"/>
        <source>ScanPath</source>
        <translation>ScanPath</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_trajectory.cpp" line="306"/>
        <source>Error loading at line %1: missing columns.</source>
        <translation>Error loading at line %1: missing columns.</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_trajectory.cpp" line="313"/>
        <source>Error loading point at line %1</source>
        <translation>Error loading point at line %1</translation>
    </message>
</context>
<context>
    <name>CT_Reader_XYB</name>
    <message>
        <location filename="../readers/ct_reader_xyb.cpp" line="19"/>
        <source>Fichiers binaire de points .xyb</source>
        <translation>Binary point files .xyb</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_xyb.cpp" line="20"/>
        <source>Chargement de points depuis un fichier format binaire XYB (FARO)</source>
        <translation>Loading points from an XYB binary format file (FARO)</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_xyb.cpp" line="33"/>
        <source>Points, Fichier XYB</source>
        <translation>Points, XYB File</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_xyb.cpp" line="139"/>
        <source>En-tête non valide</source>
        <translation>Invalid header</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_xyb.cpp" line="245"/>
        <source>Scène</source>
        <translation>Scene</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_xyb.cpp" line="246"/>
        <source>Intensité</source>
        <translation>Intensity</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_xyb.cpp" line="247"/>
        <source>Scanner</source>
        <translation>Scanner</translation>
    </message>
</context>
<context>
    <name>GPlyColorConfiguration</name>
    <message>
        <location filename="../readers/tools/ply/views/sub/gplycolorconfiguration.ui" line="14"/>
        <source>Form</source>
        <translation>Form</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/views/sub/gplycolorconfiguration.ui" line="28"/>
        <source>Canal bleu</source>
        <translation>Blue channel</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/views/sub/gplycolorconfiguration.ui" line="35"/>
        <source>Canal vert</source>
        <translation>Green channel</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/views/sub/gplycolorconfiguration.ui" line="42"/>
        <source>Canal rouge</source>
        <translation>Red channel</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/views/sub/gplycolorconfiguration.ui" line="49"/>
        <source>Canal alpha (optionnel)</source>
        <translation>Alpha channel (optional)</translation>
    </message>
</context>
<context>
    <name>GPlyNormalConfiguration</name>
    <message>
        <location filename="../readers/tools/ply/views/sub/gplynormalconfiguration.ui" line="14"/>
        <source>Form</source>
        <translation>Form</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/views/sub/gplynormalconfiguration.ui" line="28"/>
        <source>Normal Z</source>
        <translation>Normal Z</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/views/sub/gplynormalconfiguration.ui" line="35"/>
        <source>Norma Y</source>
        <translation>Normal Y</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/views/sub/gplynormalconfiguration.ui" line="42"/>
        <source>Normal X</source>
        <translation>Normal X</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/views/sub/gplynormalconfiguration.ui" line="49"/>
        <source>Courbure (optionnel)</source>
        <translation>Curvature (optional)</translation>
    </message>
</context>
<context>
    <name>GPlyReadConfiguration</name>
    <message>
        <location filename="../readers/tools/ply/views/gplyreadconfiguration.ui" line="14"/>
        <source>Configuration de la lecture du fichier PLY</source>
        <translation>Configuration of the PLY file reading</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/views/gplyreadconfiguration.ui" line="39"/>
        <source>Element</source>
        <translation>Element</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/views/gplyreadconfiguration.ui" line="58"/>
        <source>Nouveau...</source>
        <translation>New...</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/views/gplyreadconfiguration.cpp" line="86"/>
        <location filename="../readers/tools/ply/views/gplyreadconfiguration.cpp" line="178"/>
        <source>Couleur %1</source>
        <translation>Colour %1</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/views/gplyreadconfiguration.cpp" line="91"/>
        <location filename="../readers/tools/ply/views/gplyreadconfiguration.cpp" line="180"/>
        <source>Scalaire %1</source>
        <translation>Scalar %1</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/views/gplyreadconfiguration.cpp" line="96"/>
        <location filename="../readers/tools/ply/views/gplyreadconfiguration.cpp" line="182"/>
        <source>Normale %1</source>
        <translation>Normal %1</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/views/gplyreadconfiguration.cpp" line="132"/>
        <source>Type</source>
        <translation>Type</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/views/gplyreadconfiguration.cpp" line="135"/>
        <source>Points</source>
        <translation>Points</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/views/gplyreadconfiguration.cpp" line="139"/>
        <source>Couleurs</source>
        <translation>Colours</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/views/gplyreadconfiguration.cpp" line="143"/>
        <source>Scalaires</source>
        <translation>Scalars</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/views/gplyreadconfiguration.cpp" line="147"/>
        <source>Normales</source>
        <translation>Normal</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/views/gplyreadconfiguration.cpp" line="205"/>
        <source>Nouveau</source>
        <translation>New</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/views/gplyreadconfiguration.cpp" line="214"/>
        <source>Supprimer</source>
        <translation>Delete</translation>
    </message>
</context>
<context>
    <name>GPlyScalarConfiguration</name>
    <message>
        <location filename="../readers/tools/ply/views/sub/gplyscalarconfiguration.ui" line="14"/>
        <source>Form</source>
        <translation>Form</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/views/sub/gplyscalarconfiguration.ui" line="22"/>
        <source>Valeur</source>
        <translation>Value</translation>
    </message>
</context>
<context>
    <name>GPlyVertexConfiguration</name>
    <message>
        <location filename="../readers/tools/ply/views/sub/gplyvertexconfiguration.ui" line="14"/>
        <source>Form</source>
        <translation>Form</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/views/sub/gplyvertexconfiguration.ui" line="25"/>
        <source>Z</source>
        <translation>Z</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/views/sub/gplyvertexconfiguration.ui" line="32"/>
        <source>Y</source>
        <translation>Y</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/views/sub/gplyvertexconfiguration.ui" line="42"/>
        <source>X</source>
        <translation>X</translation>
    </message>
</context>
<context>
    <name>GPly_CT_ReadConfiguration_Wrapper</name>
    <message>
        <location filename="../readers/tools/ply/plycomputreewrappers.h" line="270"/>
        <source>Certains éléments ne sont pas complètement renseignés.</source>
        <translation>Some elements are not completely filled in.</translation>
    </message>
</context>
<context>
    <name>PBG_CSVConfigurationDialog</name>
    <message>
        <location filename="../views/exporters/csv/pbg_csvconfigurationdialog.ui" line="14"/>
        <source>Configuration de l&apos;exportation</source>
        <translation>Export configuration</translation>
    </message>
</context>
<context>
    <name>PBG_CSVDataRefListWidget</name>
    <message>
        <location filename="../views/exporters/csv/pbg_csvdatareflistwidget.ui" line="14"/>
        <source>Form</source>
        <translation>Form</translation>
    </message>
    <message>
        <location filename="../views/exporters/csv/pbg_csvdatareflistwidget.ui" line="35"/>
        <source>Ajouter tous</source>
        <translation>Add all</translation>
    </message>
    <message>
        <location filename="../views/exporters/csv/pbg_csvdatareflistwidget.cpp" line="51"/>
        <source>Nom</source>
        <translation>Name</translation>
    </message>
    <message>
        <location filename="../views/exporters/csv/pbg_csvdatareflistwidget.cpp" line="52"/>
        <source>Type</source>
        <translation>Type</translation>
    </message>
</context>
<context>
    <name>PBG_CSVPreviewWidget</name>
    <message>
        <location filename="../views/exporters/csv/pbg_csvpreviewwidget.ui" line="14"/>
        <source>Form</source>
        <translation>Form</translation>
    </message>
</context>
<context>
    <name>PB_ASCIDExporter</name>
    <message>
        <location filename="../exporters/ascid/pb_ascidexporter.cpp" line="12"/>
        <source>Fichier asc</source>
        <translation>Asc file</translation>
    </message>
    <message>
        <location filename="../exporters/ascid/pb_ascidexporter.cpp" line="14"/>
        <source>Exporte les points au format ASCII. Tous les items contenant des points sont exportés dans le même fichier, avec les champs suivants :&lt;br&gt;- ID : ID Computree de l&apos;item contenant le point&lt;br&gt;- X  : Coordonnée X&lt;br&gt;- Y  : Coordonnée Y&lt;br&gt;- Z  : Coordonnée Z&lt;br&gt;</source>
        <translation>Exports points in ASCII format. All items containing points are exported in the same file, with the following fields:&lt;br&gt;- ID: Computree ID of the item containing the point&lt;br&gt;- X: X coordinate&lt;br&gt;- Y: Y coordinate&lt;br&gt;- Z: Z coordinate&lt;br&gt;</translation>
    </message>
    <message>
        <location filename="../exporters/ascid/pb_ascidexporter.cpp" line="28"/>
        <source>Points + ID item, ASCII(X,Y,Z)</source>
        <translation>Points + item ID, ASCII(X,Y,Z)</translation>
    </message>
    <message>
        <location filename="../exporters/ascid/pb_ascidexporter.cpp" line="40"/>
        <source>Item à exporter</source>
        <translation>Item to be exported</translation>
    </message>
    <message>
        <location filename="../exporters/ascid/pb_ascidexporter.cpp" line="41"/>
        <source>ID</source>
        <translation>ID</translation>
    </message>
</context>
<context>
    <name>PB_ASCRGBExporter</name>
    <message>
        <location filename="../exporters/ascrgb/pb_ascrgbexporter.cpp" line="22"/>
        <source>Fichier asc</source>
        <translation>Asc file</translation>
    </message>
    <message>
        <location filename="../exporters/ascrgb/pb_ascrgbexporter.cpp" line="24"/>
        <source>Exporte les points au format ASCII, avec les champs suivants :&lt;br&gt;- X  : Coordonnée X&lt;br&gt;- Y  : Coordonnée Y&lt;br&gt;- Z  : Coordonnée Z&lt;br&gt;- R  : Composante rouge&lt;br&gt;- V  : Composante verte&lt;br&gt;- B  : Composante Bleue&lt;br&gt;- NX : Coordonnée X de la normale au point&lt;br&gt;- NY : Coordonnée Y de la normale au point&lt;br&gt;- NZ : Coordonnée Z de la normale au point&lt;br&gt;&lt;br&gt;</source>
        <translation>Exports points in ASCII format, with the following fields:&lt;br&gt;- X : X coordinate&lt;br&gt;- Y : Y coordinate&lt;br&gt;- Z : Z coordinate&lt;br&gt;- R : Red component&lt;br&gt;- V : Green component&lt;br&gt;- B : Blue component&lt;br&gt;- NX : X coordinate of the point normal&lt;br&gt;- NY : Coordonnée Y de la normale au point&lt;br&gt;- NZ : Z coordinate of the point normal&lt;br&gt;&lt;br&gt;</translation>
    </message>
    <message>
        <location filename="../exporters/ascrgb/pb_ascrgbexporter.cpp" line="43"/>
        <source>Points, ASCII(X,Y,Z,R,G,B,NX,NY,NZ)</source>
        <translation>Points, ASCII(X,Y,Z,R,G,B,NX,NY,NZ)</translation>
    </message>
    <message>
        <location filename="../exporters/ascrgb/pb_ascrgbexporter.cpp" line="60"/>
        <source>Item à exporter</source>
        <translation>Item to be exported</translation>
    </message>
    <message>
        <location filename="../exporters/ascrgb/pb_ascrgbexporter.cpp" line="61"/>
        <source>Couleurs</source>
        <translation>Colours</translation>
    </message>
    <message>
        <location filename="../exporters/ascrgb/pb_ascrgbexporter.cpp" line="62"/>
        <source>Normales</source>
        <translation>Normals</translation>
    </message>
</context>
<context>
    <name>PB_ASCXYZExporter</name>
    <message>
        <location filename="../exporters/ascxyz/pb_ascxyzexporter.cpp" line="12"/>
        <source>Fichier asc</source>
        <translation>asc file</translation>
    </message>
    <message>
        <location filename="../exporters/ascxyz/pb_ascxyzexporter.cpp" line="14"/>
        <source>Exporte les points au format ASCII. Tous les items contenant des points sont exportés dans le même fichier, avec les champs suivants :&lt;br&gt;- X  : Coordonnée X&lt;br&gt;- Y  : Coordonnée Y&lt;br&gt;- Z  : Coordonnée Z&lt;br&gt;</source>
        <translation>Exports points in ASCII format. All items containing points are exported to the same file, with the following fields:&lt;br&gt;- X: X coordinate&lt;br&gt;- Y: Y coordinate&lt;br&gt;- Z: Z coordinate&lt;br&gt;.</translation>
    </message>
    <message>
        <location filename="../exporters/ascxyz/pb_ascxyzexporter.cpp" line="27"/>
        <source>Points, ASCII(X,Y,Z)</source>
        <translation>Points, ASCII(X,Y,Z)</translation>
    </message>
    <message>
        <location filename="../exporters/ascxyz/pb_ascxyzexporter.cpp" line="39"/>
        <source>Item à exporter</source>
        <translation>Item to be exported</translation>
    </message>
</context>
<context>
    <name>PB_AsciiTrajectory</name>
    <message>
        <location filename="../exporters/asciitrajectory/pb_asciitrajectory.cpp" line="12"/>
        <source>Fichier asc</source>
        <translation>Asc file</translation>
    </message>
    <message>
        <location filename="../exporters/asciitrajectory/pb_asciitrajectory.cpp" line="14"/>
        <source>Exporte des trajectoires au format ASCII. Un fichier est créé pour chaque trajectoire, avec les champs suivants :&lt;br&gt;- Easting : Coordonnée X&lt;br&gt;- Northing : Coordonnée Y&lt;br&gt;- Height : Coordonnée Z&lt;br&gt;- Heading : Heading (degrees)&lt;br&gt;- Roll : Roll (degrees)&lt;br&gt;- Pitch : Pith (degrees)&lt;br&gt;</source>
        <translation>Exports trajectories in ASCII format. A file is created for each trajectory, with the following fields:&lt;br&gt;- Easting : X coordinate&lt;br&gt;- Northing : Y coordinate&lt;br&gt;- Height : Z coordinate&lt;br&gt;- Heading : Heading (degrees)&lt;br&gt;- Roll : Roll (degrees)&lt;br&gt;- Pitch : Pith (degrees)&lt;br&gt;</translation>
    </message>
    <message>
        <location filename="../exporters/asciitrajectory/pb_asciitrajectory.cpp" line="31"/>
        <source>Trajectoire ASCII (X,Y,Z, Heading, Roll, Pitch)</source>
        <translation>ASCII Trajectory (X,Y,Z, Heading, Roll, Pitch)</translation>
    </message>
    <message>
        <location filename="../exporters/asciitrajectory/pb_asciitrajectory.cpp" line="48"/>
        <source>Trajectoire</source>
        <translation>Trajectory</translation>
    </message>
</context>
<context>
    <name>PB_CSVExporter</name>
    <message>
        <location filename="../exporters/csv/pb_csvexporter.cpp" line="20"/>
        <source>Fichiers csv</source>
        <translation>Csv files</translation>
    </message>
    <message>
        <location filename="../exporters/csv/pb_csvexporter.cpp" line="22"/>
        <source>Exporte tous les attributs d&apos;un niveau d&apos;items (une ligne pour chaque instance d&apos;item)</source>
        <translation>Exports all attributes of an item level (one row for each item instance)</translation>
    </message>
    <message>
        <location filename="../exporters/csv/pb_csvexporter.cpp" line="40"/>
        <source>Export d&apos;attributs (csv)</source>
        <translation>Export of attributes (csv)</translation>
    </message>
    <message>
        <location filename="../exporters/csv/pb_csvexporter.cpp" line="98"/>
        <source>La méthode &quot;setItemsToExport(...)&quot; n&apos;a pas été appelée avant de restaurer la configuration de l&apos;exporter CSV.</source>
        <translation>The &quot;setItemsToExport(...)&quot; method was not called before restoring the CSV export configuration.</translation>
    </message>
    <message>
        <location filename="../exporters/csv/pb_csvexporter.cpp" line="138"/>
        <source>Item à exporter</source>
        <translation>Item to be exported</translation>
    </message>
</context>
<context>
    <name>PB_GDALExporter</name>
    <message>
        <location filename="../exporters/gdal/pb_gdalexporter.cpp" line="54"/>
        <source>Exporter GDAL de type : %1</source>
        <translation>Export GDAL type: %1</translation>
    </message>
    <message>
        <location filename="../exporters/gdal/pb_gdalexporter.cpp" line="54"/>
        <source>Inconnu</source>
        <translation>Unknown</translation>
    </message>
    <message>
        <location filename="../exporters/gdal/pb_gdalexporter.cpp" line="60"/>
        <source>Pour plus de détails voir : http://www.gdal.org/formats_list.html</source>
        <translation>For more details see: http://www.gdal.org/formats_list.html</translation>
    </message>
    <message>
        <location filename="../exporters/gdal/pb_gdalexporter.cpp" line="66"/>
        <source>Pour plus de détails voir : http://www.gdal.org/ogr_formats.html</source>
        <translation>For more details see: http://www.gdal.org/ogr_formats.html</translation>
    </message>
    <message>
        <location filename="../exporters/gdal/pb_gdalexporter.cpp" line="71"/>
        <source>Extension : </source>
        <translation>Extension : </translation>
    </message>
    <message>
        <location filename="../exporters/gdal/pb_gdalexporter.cpp" line="233"/>
        <source>Rasters</source>
        <translation>Rasters</translation>
    </message>
    <message>
        <location filename="../exporters/gdal/pb_gdalexporter.cpp" line="235"/>
        <source>Données vectorielles</source>
        <translation>Vector data</translation>
    </message>
    <message>
        <location filename="../exporters/gdal/pb_gdalexporter.cpp" line="350"/>
        <location filename="../exporters/gdal/pb_gdalexporter.cpp" line="473"/>
        <location filename="../exporters/gdal/pb_gdalexporter.cpp" line="480"/>
        <source>Creation of output file failed.</source>
        <translation>Creation of output file failed.</translation>
    </message>
    <message>
        <location filename="../exporters/gdal/pb_gdalexporter.cpp" line="359"/>
        <source>Layer creation failed.</source>
        <translation>Layer creation failed.</translation>
    </message>
    <message>
        <location filename="../exporters/gdal/pb_gdalexporter.cpp" line="419"/>
        <source>Creation of a field failed.</source>
        <translation>Creation of a field failed.</translation>
    </message>
    <message>
        <location filename="../exporters/gdal/pb_gdalexporter.cpp" line="430"/>
        <source>Creation of output file (fields names) failed.</source>
        <translation>Creation of output file (fields names) failed.</translation>
    </message>
    <message>
        <location filename="../exporters/gdal/pb_gdalexporter.cpp" line="713"/>
        <source>Failed to create feature in shapefile.</source>
        <translation>Failed to create feature in shapefile.</translation>
    </message>
</context>
<context>
    <name>PB_Grid2DExporter</name>
    <message>
        <location filename="../exporters/grid2d/pb_grid2dexporter.cpp" line="7"/>
        <source>Fichiers Grid 2D (ASCII)</source>
        <translation>2D Grid Files (ASCII)</translation>
    </message>
    <message>
        <location filename="../exporters/grid2d/pb_grid2dexporter.cpp" line="8"/>
        <source>Export des rasters au format ASCII ESRI Grid  (1 fichier par raster)</source>
        <translation>Export of rasters in ASCII ESRI Grid format (1 file per raster)</translation>
    </message>
    <message>
        <location filename="../exporters/grid2d/pb_grid2dexporter.cpp" line="18"/>
        <source>Grilles 2D, ACSII ESRI Grid</source>
        <translation>2D grids, ACSII ESRI Grid</translation>
    </message>
    <message>
        <location filename="../exporters/grid2d/pb_grid2dexporter.cpp" line="36"/>
        <source>Item à exporter</source>
        <translation>Item to be exported</translation>
    </message>
</context>
<context>
    <name>PB_Grid3DAsTableExporter</name>
    <message>
        <location filename="../exporters/grid3d/pb_grid3dastableexporter.cpp" line="7"/>
        <source>Fichiers txt</source>
        <translation>Txt files</translation>
    </message>
    <message>
        <location filename="../exporters/grid3d/pb_grid3dastableexporter.cpp" line="8"/>
        <source>Exporte des grilles 3D au format table ASCII. Les champs suivants sont exportés :&lt;br&gt;- X  : Coordonnée X de la cellule dans la grille (ligne)&lt;br&gt;- Y  : Coordonnée Y de la cellule dans la grille (colonne)&lt;br&gt;- Z  : Coordonnée Z de la cellule dans la grille (niveau Z)&lt;br&gt;- Valeur  : Valeur dans la cellule&lt;br&gt;</source>
        <translation>Exports 3D grids in ASCII table format. The following fields are exported:&lt;br&gt;- X : X coordinate of the cell in the grid (row)&lt;br&gt;- Y : Y coordinate of the cell in the grid (column)&lt;br&gt;- Z : Z coordinate of the cell in the grid (Z level)&lt;br&gt;- Value : Value in the cell&lt;br&gt;</translation>
    </message>
    <message>
        <location filename="../exporters/grid3d/pb_grid3dastableexporter.cpp" line="23"/>
        <source>Grilles 3D, table (X,Y,Z,Valeur)</source>
        <translation>3D grids, table (X,Y,Z,Value)</translation>
    </message>
    <message>
        <location filename="../exporters/grid3d/pb_grid3dastableexporter.cpp" line="41"/>
        <source>Item à exporter</source>
        <translation>Item to be exported</translation>
    </message>
</context>
<context>
    <name>PB_Grid3DExporter</name>
    <message>
        <location filename="../exporters/grid3d/pb_grid3dexporter.cpp" line="7"/>
        <source>Fichiers Grilles 3D (ASCII)</source>
        <translation>3D Grid Files (ASCII)</translation>
    </message>
    <message>
        <location filename="../exporters/grid3d/pb_grid3dexporter.cpp" line="8"/>
        <source>Export des Grilles 3D au format ASCII, inspiré du format ASCII ESRI GRID pour les rasters (1 fichier par grille)</source>
        <translation>Export of 3D Grids in ASCII format, inspired by the ESRI GRID ASCII format for rasters (1 file per grid)</translation>
    </message>
    <message>
        <location filename="../exporters/grid3d/pb_grid3dexporter.cpp" line="18"/>
        <source>Grilles 3D, ACSII</source>
        <translation>3D grids, ACSII</translation>
    </message>
    <message>
        <location filename="../exporters/grid3d/pb_grid3dexporter.cpp" line="36"/>
        <source>Item à exporter</source>
        <translation>Item to be exported</translation>
    </message>
</context>
<context>
    <name>PB_GroupDataExporter</name>
    <message>
        <location filename="../exporters/groupdata/pb_groupdataexporter.cpp" line="11"/>
        <source>Fichier txt</source>
        <translation>Txt file</translation>
    </message>
    <message>
        <location filename="../exporters/groupdata/pb_groupdataexporter.cpp" line="13"/>
        <source>Exporte tous les attributs de TOUS LES ITEMS d&apos;un niveau ou plusieurs niveaux de groupes.&lt;br&gt;Un fichier table ASCII est produit pour chaque niveau de groupe séléctionné.&lt;br&gt;Dans chaque table, il y a une ligne par instance de groupe.&lt;br&gt;Dans chaque table :&lt;br&gt;- une première ligne d&apos;entête donne le nom des items contenus dans le groupe,&lt;br&gt;- une seconde  ligne d&apos;entête donne le nom de l&apos;attribut dans l&apos;item.&lt;br&gt;De plus les deux premières colonnes de chaque table permettent de faire des jointures entre niveaux de groupes :&lt;br&gt;- GroupID  : identifiant Computree des groupes décris dans la table en cours,&lt;br&gt;- ParentID : identifiant Computree des groupes parents, contenant les groupes de la table.</source>
        <translation>Exports all attributes of ALL ITEMS of one or more group levels.&lt;br&gt;An ASCII table file is produced for each selected group level.&lt;br&gt;In each table, there is one row per group instance.&lt;br&gt;In each table:&lt;br&gt;- a first header row gives the name of the items contained in the group,&lt;br&gt;- a second header row gives the name of the attribute in the item.&lt;br&gt;In addition, the first two columns of each table allow joins to be made between levels of groups:&lt;br&gt;- GroupID: Computree identifier of the groups described in the current table,&lt;br&gt;- ParentID: Computree identifier of the parent groups, containing the groups in the table.</translation>
    </message>
    <message>
        <location filename="../exporters/groupdata/pb_groupdataexporter.cpp" line="31"/>
        <source>Export des attributs des items d&apos;un groupe</source>
        <translation>Export of attributes of items in a group</translation>
    </message>
    <message>
        <location filename="../exporters/groupdata/pb_groupdataexporter.cpp" line="43"/>
        <source>Groupe à exporter</source>
        <translation>Group to be exported</translation>
    </message>
</context>
<context>
    <name>PB_MeshObjExporter</name>
    <message>
        <location filename="../exporters/mesh/pb_meshobjexporter.cpp" line="13"/>
        <source>Fichiers .obj</source>
        <translation>.obj files</translation>
    </message>
    <message>
        <location filename="../exporters/mesh/pb_meshobjexporter.cpp" line="15"/>
        <source>Exporte un maillage dans un fichier au format OBJ (Objet 3D)</source>
        <translation>Exports a mesh to a file in OBJ (3D Object) format</translation>
    </message>
    <message>
        <location filename="../exporters/mesh/pb_meshobjexporter.cpp" line="25"/>
        <source>Maillage 3D (Mesh), format OBJ</source>
        <translation>3D mesh (Mesh), OBJ format</translation>
    </message>
    <message>
        <location filename="../exporters/mesh/pb_meshobjexporter.cpp" line="37"/>
        <source>Maillage à exporter</source>
        <translation>Mesh to be exported</translation>
    </message>
</context>
<context>
    <name>PB_OPFExporter</name>
    <message>
        <location filename="../exporters/topology/pb_opfexporter.cpp" line="25"/>
        <source>Fichiers AmapStudio .opf</source>
        <translation>AmapStudio .opf files</translation>
    </message>
    <message>
        <location filename="../exporters/topology/pb_opfexporter.cpp" line="27"/>
        <source>Exporte une topologie décrivant l&apos;architecture de végétaux dans un fichier au format OPF, pour utilisation par le logiciel AMAPStudio.&lt;br&gt;http://amapstudio.cirad.fr</source>
        <translation>Exports a topology describing the plant architecture to an OPF file for use by AMAPStudio software.http://amapstudio.cirad.fr</translation>
    </message>
    <message>
        <location filename="../exporters/topology/pb_opfexporter.cpp" line="38"/>
        <source>Topologie, format OPF</source>
        <translation>Topology, OPF format</translation>
    </message>
    <message>
        <location filename="../exporters/topology/pb_opfexporter.cpp" line="55"/>
        <source>Groupe OPF à exporter</source>
        <translation>OPF group to be exported</translation>
    </message>
</context>
<context>
    <name>PB_Polygon2DExporter</name>
    <message>
        <location filename="../exporters/polygon2d/pb_polygon2dexporter.cpp" line="7"/>
        <source>Polygones 2D (ASCII)</source>
        <translation>2D polygons (ASCII)</translation>
    </message>
    <message>
        <location filename="../exporters/polygon2d/pb_polygon2dexporter.cpp" line="8"/>
        <source>Exporte des Polygones 2D en format ASCII. Le fichier de sortie contient une ligne par polygones.&lt;br&gt;Pour chaque polygone, sont exportés :&lt;br&gt;- PolygonId : Identifiant Computree du polygone&lt;br&gt;- AreaOfPolygon : Aire du polygone&lt;br&gt;- Xcenter : Coordonnée X du centre de masse du polygone&lt;br&gt;- Ycenter : Coordonnée Y du centre de masse du polygone&lt;br&gt;- NumberOfVertice(N) : Nombre de sommets du polygone&lt;br&gt;- Xvertice1 : Coordonnée X du 1er sommet&lt;br&gt;- Yvertice1 : Coordonnée Y du 1er sommet&lt;br&gt;- Xvertice2 : Coordonnée X du 2ième sommet&lt;br&gt;- Yvertice2 : Coordonnée Y du 2ième sommet&lt;br&gt;...- XverticeN : Coordonnée X du Nième sommet&lt;br&gt;- YverticeN : Coordonnée Y du Nième sommet&lt;br&gt;N.B. : Le nombre de colonnes varie donc pour chaque ligne. </source>
        <translation>Exports 2D Polygons in ASCII format. The output file contains one line per polygon.&lt;br&gt;For each polygon, are exported :&lt;br&gt;- PolygonId : Computree identifier of the polygon&lt;br&gt;- AreaOfPolygon : Area of the polygon&lt;br&gt;- Xcenter : X coordinate of the centre of mass of the polygon&lt;br&gt;- Ycenter : Y coordinate of the centre of mass of the polygon&lt;br&gt;- NumberOfVertice(N): Number of vertices in the polygon&lt;br&gt;- Xvertice1 : X coordinate of the 1st vertex&lt;br&gt;- Yvertice1 : Y coordinate of the 1st vertex&lt;br&gt;- Xvertice2 : X coordinate of the 2nd vertex&lt;br&gt;- Yvertice2 : Y coordinate of the 2nd vertex&lt;br&gt;...- XverticeN : X coordinate of the Nth vertex&lt;br&gt;- YverticeN : Y coordinate of the Nth vertex&lt;br&gt;N.B. : The number of columns therefore varies for each row. </translation>
    </message>
    <message>
        <location filename="../exporters/polygon2d/pb_polygon2dexporter.cpp" line="32"/>
        <source>Polygones 2D, ACSII</source>
        <translation>2D polygons, ACSII</translation>
    </message>
    <message>
        <location filename="../exporters/polygon2d/pb_polygon2dexporter.cpp" line="44"/>
        <source>Item à exporter</source>
        <translation>Item to be exported</translation>
    </message>
</context>
<context>
    <name>PB_ProfileExporter</name>
    <message>
        <location filename="../exporters/profile/pb_profileexporter.cpp" line="7"/>
        <source>Fichiers Profile (ASCII)</source>
        <translation>Profile files (ASCII)</translation>
    </message>
    <message>
        <location filename="../exporters/profile/pb_profileexporter.cpp" line="8"/>
        <source>Export de profils au format ASCII (1 fichier par profil).&lt;br&gt;Le fichier comporte d&apos;abord une entête inspirée du format ASCII ESRI GRID pour les rasters, décrivant l&apos;origine, la direction et la résolution du profil.&lt;br&gt;Ensuite, une table fournit les champs suivants :&lt;br&gt;- Level : Numéro de la cellule dans le profil&lt;br&gt;- Length : Longueur correspondant au centre de la cellule le long du profil&lt;br&gt;- Xc : Coordonnée X du centre de la cellule&lt;br&gt;- Yc : Coordonnée Y du centre de la cellule&lt;br&gt;- Zc : Coordonnée Z du centre de la cellule&lt;br&gt;- Value : Valeur de la cellule</source>
        <translation>Export of profiles in ASCII format (1 file per profile).&lt;br&gt;The file first includes a header inspired by the ESRI GRID ASCII format for rasters, describing the origin, direction and resolution of the profile.&lt;br&gt;Next, a table provides the following fields:&lt;br&gt;- Level : Number of the cell in the profile&lt;br&gt;- Length : Length corresponding to the centre of the cell along the profile&lt;br&gt;- Xc : X coordinate of the cell centre&lt;br&gt;- Yc : Y coordinate of the cell centre&lt;br&gt;- Zc : Z coordinate of the cell centre&lt;br&gt;- Value : Value of the cell</translation>
    </message>
    <message>
        <location filename="../exporters/profile/pb_profileexporter.cpp" line="27"/>
        <source>Profils, ACSII</source>
        <translation>Profiles, ACSII</translation>
    </message>
    <message>
        <location filename="../exporters/profile/pb_profileexporter.cpp" line="45"/>
        <source>Item à exporter</source>
        <translation>Item to be exported</translation>
    </message>
</context>
<context>
    <name>PB_XYBExporter</name>
    <message>
        <location filename="../exporters/xyb/pb_xybexporter.cpp" line="17"/>
        <source>Fichiers binaire de points .xyb</source>
        <translation>Binary point files .xyb</translation>
    </message>
    <message>
        <location filename="../exporters/xyb/pb_xybexporter.cpp" line="18"/>
        <source>Export des points dans un fichier format binaire XYB (FARO)</source>
        <translation>Export of points in a binary XYB file (FARO)</translation>
    </message>
    <message>
        <location filename="../exporters/xyb/pb_xybexporter.cpp" line="28"/>
        <source>Export de points, XYB (X,Y,Z,I)</source>
        <translation>Export of points, XYB (X,Y,Z,I)</translation>
    </message>
    <message>
        <location filename="../exporters/xyb/pb_xybexporter.cpp" line="46"/>
        <source>- Aucun points à exporter</source>
        <translation>- No points to export</translation>
    </message>
    <message>
        <location filename="../exporters/xyb/pb_xybexporter.cpp" line="77"/>
        <source>Item à exporter</source>
        <translation>Item to be exported</translation>
    </message>
    <message>
        <location filename="../exporters/xyb/pb_xybexporter.cpp" line="78"/>
        <source>Scanner</source>
        <translation>Scanner</translation>
    </message>
    <message>
        <location filename="../exporters/xyb/pb_xybexporter.cpp" line="79"/>
        <source>Couleurs</source>
        <translation>Colours</translation>
    </message>
</context>
<context>
    <name>PB_XYBPieceByPiecePrivateExporter</name>
    <message>
        <location filename="../exporters/xyb/private/pb_xybpiecebypieceprivateexporter.cpp" line="146"/>
        <source>Export du fichier %1 terminé</source>
        <translation>Export of file %1 completed</translation>
    </message>
</context>
<context>
    <name>QObject</name>
    <message>
        <location filename="../readers/ct_reader_asciigrid3d.cpp" line="5"/>
        <source>Line %1 must begin with &quot;%2&quot; but we read : &quot;%3&quot;</source>
        <translation>Line %1 must begin with &quot;%2&quot; but we read : &quot;%3&quot;</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_asciigrid3d.cpp" line="6"/>
        <source>Unable to convert the ascii format to a %1 in header at line %2</source>
        <translation>Unable to convert the ascii format to a %1 in header at line %2</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_points_ascii.cpp" line="14"/>
        <source>Intensité</source>
        <translation>Intensity</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_points_ascii.cpp" line="15"/>
        <source>Rouge</source>
        <translation>Red</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_points_ascii.cpp" line="16"/>
        <source>Vert</source>
        <translation>Green</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_points_ascii.cpp" line="17"/>
        <source>Bleu</source>
        <translation>Blue</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_points_ascii.cpp" line="18"/>
        <source>Normale X</source>
        <translation>Normal X</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_points_ascii.cpp" line="19"/>
        <source>Normale Y</source>
        <translation>Normal Y</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_points_ascii.cpp" line="20"/>
        <source>Normale Z</source>
        <translation>Normal Z</translation>
    </message>
    <message>
        <location filename="../readers/ct_reader_points_ascii.cpp" line="21"/>
        <source>Normale Curvature</source>
        <translation>Normal Curvature</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_gdalheader.h" line="33"/>
        <source>Min X</source>
        <translation>Min X</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_gdalheader.h" line="34"/>
        <source>Max X</source>
        <translation>Max X</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_gdalheader.h" line="35"/>
        <source>Min Y</source>
        <translation>Min Y</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_gdalheader.h" line="36"/>
        <source>Max Y</source>
        <translation>Max Y</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_plyheader.h" line="63"/>
        <source>Format</source>
        <translation>Format</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_plyheader.h" line="64"/>
        <source>Version</source>
        <translation>Version</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_plyheader.h" line="65"/>
        <source>Number of elements</source>
        <translation>Number of elements</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_plyheader.h" line="66"/>
        <source>Number of properties</source>
        <translation>Number of properties</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_plyheader.h" line="67"/>
        <source>Is valid</source>
        <translation>Is valid</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_xybheader.h" line="46"/>
        <source>Scan Center X</source>
        <translation>Scan Center X</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_xybheader.h" line="47"/>
        <source>Scan Center Y</source>
        <translation>Scan Center Y</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_xybheader.h" line="48"/>
        <source>Scan Center Z</source>
        <translation>Scan Center Z</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_xybheader.h" line="49"/>
        <source>Scan rows number</source>
        <translation>Scan rows number</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_xybheader.h" line="50"/>
        <source>Scan columns number</source>
        <translation>Scan columns number</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/internal/plytype.h" line="127"/>
        <source>Ascii</source>
        <translation>Ascii</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/internal/plytype.h" line="129"/>
        <source>Binary little endian</source>
        <translation>Binary little endian</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/internal/plytype.h" line="131"/>
        <source>Binary big endian</source>
        <translation>Binary big endian</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/internal/plytype.h" line="133"/>
        <source>Unknown</source>
        <translation>Unknown</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/internal/plytype.h" line="141"/>
        <source>char</source>
        <translation>char</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/internal/plytype.h" line="143"/>
        <source>uchar</source>
        <translation>uchar</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/internal/plytype.h" line="145"/>
        <source>short</source>
        <translation>short</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/internal/plytype.h" line="147"/>
        <source>ushort</source>
        <translation>ushort</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/internal/plytype.h" line="149"/>
        <source>int</source>
        <translation>int</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/internal/plytype.h" line="151"/>
        <source>uint</source>
        <translation>uint</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/internal/plytype.h" line="153"/>
        <source>float</source>
        <translation>float</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/internal/plytype.h" line="155"/>
        <source>double</source>
        <translation>double</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/internal/plytype.h" line="157"/>
        <source>unknown</source>
        <translation>unknown</translation>
    </message>
    <message>
        <location filename="../readers/tools/ply/plyheaderreader.cpp" line="197"/>
        <source>Inconnu</source>
        <translation>Unknown</translation>
    </message>
    <message>
        <location filename="../tools/ct_readerstools.h" line="126"/>
        <source>ERREUR : aucun reader disponible</source>
        <translation>ERROR: no reader available</translation>
    </message>
    <message>
        <location filename="../tools/ct_configurableelementtools.h" line="132"/>
        <source>&lt;h3&gt;%2&lt;/h3&gt;&lt;div class=&quot;descBlocklvl2&quot;&gt;&lt;strong&gt;Plugin&lt;/strong&gt; : %5, &lt;strong&gt;Nom de classe&lt;/strong&gt; : %1&lt;br&gt;&lt;br&gt;&lt;strong&gt;Description&lt;/strong&gt;&lt;br&gt;&lt;br&gt;%3&lt;br&gt;&lt;br&gt;%6%4&lt;/div&gt;</source>
        <translation>&lt;h3&gt;%2&lt;/h3&gt;&lt;div class=&quot;descBlocklvl2&quot;&gt;&lt;strong&gt;Plugin&lt;/strong&gt;: %5, &lt;strong&gt;Class name&lt;/strong&gt;: %1&lt;br&gt;&lt;br&gt;&lt;strong&gt;Description&lt;/strong&gt;&lt;br&gt;&lt;br&gt;%3&lt;br&gt;&lt;br&gt;%6%4&lt;/div&gt;</translation>
    </message>
    <message>
        <location filename="../tools/ct_configurableelementtools.h" line="146"/>
        <source>&lt;strong&gt;Détails&lt;/strong&gt;&lt;br&gt;&lt;br&gt;</source>
        <translation>&lt;strong&gt;Details&lt;/strong&gt;&lt;br&gt;&lt;br&gt;</translation>
    </message>
    <message>
        <location filename="../tools/ct_configurableelementtools.h" line="149"/>
        <source>&lt;br&gt;</source>
        <translation>&lt;br&gt;</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_ctiheader.h" line="93"/>
        <source>fileFormat</source>
        <translation>fileFormat</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_ctiheader.h" line="94"/>
        <source>areaShapeType</source>
        <translation>areaShapeType</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_ctiheader.h" line="95"/>
        <source>areaSmallShapeType</source>
        <translation>areaSmallShapeType</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_ctiheader.h" line="96"/>
        <source>xmin</source>
        <translation>xmin</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_ctiheader.h" line="97"/>
        <source>ymin</source>
        <translation>ymin</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_ctiheader.h" line="98"/>
        <source>xmax</source>
        <translation>xmax</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_ctiheader.h" line="99"/>
        <source>ymax</source>
        <translation>ymax</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_ctiheader.h" line="100"/>
        <source>basePath</source>
        <translation>basePath</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_trjheader.h" line="48"/>
        <source>TSCANTRJ</source>
        <translation>TSCANTRJ</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_trjheader.h" line="49"/>
        <source>File version</source>
        <translation>File version</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_trjheader.h" line="50"/>
        <source>Number of position records</source>
        <translation>Number of position records</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_trjheader.h" line="51"/>
        <source>Description</source>
        <translation>Description</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_trjheader.h" line="52"/>
        <source>First time stamp</source>
        <translation>First time stamp</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_trjheader.h" line="53"/>
        <source>Last time stamp</source>
        <translation>Last time stamp</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_trjheader.h" line="54"/>
        <source>Original number</source>
        <translation>Original number</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_trjheader.h" line="55"/>
        <source>Line number</source>
        <translation>Line number</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_trjheader.h" line="56"/>
        <source>Group</source>
        <translation>Group</translation>
    </message>
    <message>
        <location filename="../readers/headers/ct_trjheader.h" line="57"/>
        <source>HdrSize</source>
        <translation>HdrSize</translation>
    </message>
</context>
</TS>
