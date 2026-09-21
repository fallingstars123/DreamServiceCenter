# Letter Inspection

Runtime Unreal Engine plugin providing:

- `AInspectableLetter`: inspectable letter actor and presentation metadata.
- `ULetterInspectComponent`: player-side inspection, camera DOF, light, input lock, and UI orchestration.
- `ULetterDescriptionWidget`: Blueprint-extensible description widget base class.

Bundled Blueprint assets:

- `/LetterInspection/Blueprints/MyInspectableLetter`
- `/LetterInspection/Widgets/MyLetterDescriptionWidget`

## Integration

The plugin now bootstraps itself in Game/PIE worlds. It finds the locally controlled pawn, adds one transient `ULetterInspectComponent`, finds the active camera, and creates the camera-relative inspect point. No binary edit to `BP_Astronaut` is required.

- `F` toggles letter scan mode.
- Hold the left mouse button while looking at an `AInspectableLetter` to scan it.
- The default scan takes `0.45` seconds and uses an `8 cm` sphere trace with `0.12` seconds of target grace to avoid crosshair flicker.
- A completed scan calls `BeginInspect` by default.
- Press `Escape` to leave the close-up inspection view.
- Set the console variable `LetterInspection.AutoBootstrap 0` to disable the automatic player component.

For a manually configured player component, turn off `bUseDefaultScanInput` and call `SetScanModeActive` plus `SetScanInputHeld` from the project's input graph.

1. Derive a Widget Blueprint from `ULetterDescriptionWidget` and assign it to `DescriptionWidgetClass` on a manually added component when a custom description UI is required.
   - Create an `Is Variable` Text Block named `LetterTitleTextBlock` for the heading.
   - Create an `Is Variable` Text Block named `LetterBodyTextBlock` for the body paragraph. Put it inside a width-constrained `Size Box`; native code enables automatic wrapping.
   - `SetupLetterContent` remains available as an optional Blueprint event for additional presentation logic and backwards compatibility.
2. Derive scannable letter/object Blueprints from `AInspectableLetter`. The active mesh must block the configured scan trace channel (`Visibility` by default).

In DreamServiceCenter, `AInspectableLetter` also registers its generated class with `/Game/Blueprints/BPI_Scannable` at runtime. Its `GetScanInfo` implementation maps `LetterTitle`, `LetterDescription`, `ScanObjectIcon`, `ScanObjectType`, `ScanStabilityImpact`, `ScanAnomalyLevel`, and `ScanSystemDirective` into the existing `BP_Astronaut` visor scanner. This keeps the visor marker/progress UI and the close-up inspection system on the same target actor.

Use `Visor Scannable Actor` for an ordinary prop that should display only the
existing blue `WBP_VisorHUD` scan panel. Place it in a level (or create a
Blueprint child), assign `Scan Mesh`, and fill the `Scannable > Information`
fields. It registers with `BPI_Scannable` and blocks the Visibility trace
automatically. Play from `Persistent`, press `F`, aim within 3000 cm, and hold
the left mouse button for 3 seconds.

The delegates `OnScanModeChanged`, `OnScanTargetChanged`, `OnScanProgressChanged`, and `OnScanCompleted` are available for the existing visor HUD or other Blueprint UI.

## Mesh selection

`AInspectableLetter` keeps the original `LetterMesh` static-mesh component for backward compatibility and also provides `SkeletalLetterMesh`.

- Call `SetStaticLetterMesh` to assign and activate a static mesh.
- Call `SetSkeletalLetterMesh` to assign and activate a skeletal mesh.
- Use `SetLetterMeshType` when both component assets are configured in a Blueprint.

The inspection component automatically uses the active mesh for physics state and size normalization.

The bundled actor Blueprint keeps its current project mesh assignment. For a reusable letter, replace that asset in the Blueprint defaults or call one of the two mesh setter functions at runtime.
