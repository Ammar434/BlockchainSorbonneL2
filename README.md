# BlockchainSorbonneL2
Nous consid´erons dans ce projet l’organisation d’un processus ´electoral par scrutin uninominal majoritaire a deux tours (comme ici en France).
— Partie 1 : Implementation d’outils de cryptographie.
— Partie 2 : Creation d’un syst`eme de d´eclarations s´ecuris´es par chiffrement asymetrique.
— Partie 3 : Manipulation d’une base centralis´ee de d´eclarations.
— Partie 4 : Impl´ementation d’un m´ecanisme de consensus.
— Partie 5 : Manipulation d’une base d´ecentralis´ee de d´eclarations.
Chaque partie est divis´ee en exercices, qui vont vous permettre de concevoir progressivement le programme final. Il est imperatif de travailler r´eguli`erement afin de ne pas prendre de retard et de pouvoir
profiter des s´eances correspondantes pour chaque partie du projet.

Cadre du projet
Dans ce projet, nous consid´erons la probl´ematique de d´esignation du vainqueur d’un processus ´electoral.
Dans un processus ´electoral, chaque participant peut d´eclarer sa candidature au scrutin et/ou donner
sa voix `a un candidat d´eclar´e. La tenue d’un processus ´electoral a, depuis toujours, pos´e des questions
de confiance et de transparence ´epineuses, dans la mesure o`u les ´elections sont g´en´eralement organis´ees par le syst`eme ex´ecutif en place, qui est souvent candidat `a sa r´e´election et donc soup¸conn´e
d’interf´erences. De plus, le compte des voix fait appel `a des assesseurs, ce qui en fait un travail long et
avec peu de garanties de fiabilit´e, dans la mesure o`u tout le monde ne peut pas v´erifier que le compte
a eu lieu dans des conditions honnˆetes. Enfin, le caract`ere anonyme de la d´esignation par bulletin fait
que personne ne peut v´erifier a posteriori que sa voix a ´et´e comptabilis´ee chez le bon candidat.
Un autre aspect `a consid´erer est celui de l’ergonomie pour le votant. Plus pr´ecis´ement, un syst`eme
d´ecentralis´e permettrait un vote `a distance, et le vote `a distance (tout comme le vote par correspondance) a longtemps ´et´e envisag´e comme un outil pour combattre l’abstention, qui a atteint un record
historique lors des des ´elections r´egionales et d´epartementales de juin 2021 (66,7 % et allant jusqu’`a
87 % chez les jeunes de moins de 25 ans). Un projet de loi a par ailleurs ´et´e d´epos´e `a l’assembl´ee
nationale le 21 septembre 2021, qui permettrait le vote par correspondance. Ce projet de loi serait un
premier pas vers le vote ´electronique, avec comme argument principal le fait que le vote postal a ´et´e
instaur´e en Outre-Rhin en 1957, justifiant possiblement l’´ecart entre le taux d’abstention en France
et celui de l’Allemagne (qui ne d´epasse pas les 33%).
L’objectif de ce projet est donc de proposer une piste de r´eflexion sur les protocoles et sur les structures
de donn´ees `a mettre en place pour permettre d’impl´ementer efficacement le processus de d´esignation
du vainqueur de l’´election, tout en garantissant l’int´egrit´e, la s´ecurit´e et la transparence de l’´election
