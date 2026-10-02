# Universal-Updater publication

Universal-Updater can install the plugin using the `downloadRelease` action. The release asset name is fixed as:

`InazumaElevenCTRPF-unistore.zip`

The archive root must contain `luma/`, so extraction to `sdmc:/` produces:

`sdmc:/luma/plugins/<title-id>/InazumaElevenCTRPF.3gx`

## Before publishing

1. Create a public GitHub repository named `InazumaElevenCTRPF`.
2. Replace every `PROJECT_OWNER` value in `unistore/inazuma-eleven-ctrpf.unistore` with the GitHub owner or organisation.
3. Commit the source, license, README and `unistore/` directory.
4. Create a tagged GitHub release such as `v0.1.0`.
5. Upload the install archive to that release using the exact filename `InazumaElevenCTRPF-unistore.zip`.

## Custom-store testing

After the repository is public, add this URL in Universal-Updater under Settings > Select UniStore > Add:

`https://raw.githubusercontent.com/Stevelee72/InazumaElevenCTRPF/main/unistore/inazuma-eleven-ctrpf.unistore`

This tests downloading and extraction before submitting the project to Universal-DB. A QR code can encode the same raw URL.

## Default Universal-DB listing

Once the release installation has been tested, submit the public repository to Universal-Team's Universal-DB. Universal-DB generates the default Universal-Updater catalogue from its source metadata; acceptance is controlled by the Universal-Team maintainers.

Do not submit an untested memory-editing build to the default catalogue. First verify title detection and the baseline editor addresses on hardware for each game family.
