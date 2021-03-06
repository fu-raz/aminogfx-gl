'use strict';

const amino = require('../../main.js');

/**
 * Play video.
 *
 * @param {object} opts
 * @param {function} done
 */
function playVideo(opts, done) {
    const gfx = new amino.AminoGfx(opts.gfxOpts);

    gfx.start(function (err) {
        if (err) {
            console.log('Amino error: ' + err.message);
            done(err);
            return;
        }

        //video
        const video = new amino.AminoVideo();

        video.src = opts.src;
        video.opts = opts.opts;

        if (opts.loop !== undefined) {
            video.loop = opts.loop;
        }

        //image view
        const dispW = this.w();
        const dispH = this.h();
        const iv = this.createImageView().w(dispW).h(dispH).position('center top').size('contain').src(video);

        iv.w.bindTo(this.w);
        iv.h.bindTo(this.h);

        //events
        iv.image.watch(video => {
            if (video) {
                video.addEventListener(event => {
                    console.log('video event: ' + event);
                });

                if (opts.ready) {
                    opts.ready(video);
                }
            }
        });

        //display info
        console.log('display size: ' + dispW + 'x' + dispH);

        done(null, video, iv);

        this.root.add(iv);
    });
}

exports.playVideo = playVideo;

let time;

/**
 * Start measuring interval.
 */
function measureStart() {
    time = new Date().getTime();
}

/**
 * Stop measuring.
 *
 * @param {*} name
 */
function measureEnd(name) {
    const now = new Date().getTime();

    console.log(name + ': ' + (now - time) + ' ms');
}

exports.measureStart = measureStart;
exports.measureEnd = measureEnd;