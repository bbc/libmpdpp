#include <limits.h>
#include <stdlib.h>

#include <functional>
#include <iostream>
#include <vector>

#include "libmpd++/SegmentTemplate.hh"

LIBPARSEMPD_NAMESPACE_USING_ALL;

bool test_segment_template_default()
{
    SegmentTemplate seg_temp;
    SegmentTemplate::Variables vars("repId", 1, 2, 3, 4);

    if (seg_temp.applyMediaTemplate(vars) != "") {
        std::cerr << "SegmentTemplate.applyMediaTemplate() failed when no @media template is set" << std::endl;
        return false;
    }

    if (seg_temp.applyIndexTemplate(vars) != "") {
        std::cerr << "SegmentTemplate.applyIndexTemplate() failed when no @index template is set" << std::endl;
        return false;
    }

    if (seg_temp.applyInitializationTemplate(vars) != "") {
        std::cerr << "SegmentTemplate.applyInitializationTemplate() failed when no @initialization template is set" << std::endl;
        return false;
    }

    if (seg_temp.applyBitstreamSwitchingTemplate(vars) != "") {
        std::cerr << "SegmentTemplate.applyBitstreamSwitchingTemplate() failed when no @bitstreamSwitching template is set"
                  << std::endl;
        return false;
    }

    return true;
}

bool test_segment_template_media_template()
{
    SegmentTemplate seg_temp;
    seg_temp.media("$$/$RepresentationId$/$Number%06d$/$Bandwidth$/$Time%03d$/$SubNumber$/$Nonsense$/$FurtherNonsense$Number$");
    SegmentTemplate::Variables vars("repId", 1, 2, 3000, 4);

    auto media_url = seg_temp.applyMediaTemplate(vars);
    if (media_url != "$/repId/000001/2/3000/4/$Nonsense$/$FurtherNonsense1") {
        std::cerr << "SegmentTemplate.applyMediaTemplate() failed: expected \"$/repId/000001/2/3000/4/$Nonsense$/$FurtherNonsense1\" got \"" << media_url << "\"" << std::endl;
        return false;
    }

    return true;
}

bool test_segment_template_vars_missing()
{
    SegmentTemplate seg_temp;
    seg_temp.media("$$/$RepresentationId$/$Number%06d$/$Bandwidth$/$Time%03d$/$SubNumber$/$Nonsense$/$FurtherNonsense$Number$");

    SegmentTemplate::Variables vars("repId", 1, 2, 3000);
    auto media_url = seg_temp.applyMediaTemplate(vars);
    if (media_url != "$/repId/000001/2/3000/$SubNumber$/$Nonsense$/$FurtherNonsense1") {
        std::cerr << "SegmentTemplate.applyMediaTemplate() failed: expected \"$/repId/000001/2/3000/$SubNumber$/$Nonsense$/$FurtherNonsense1\" got \"" << media_url << "\"" << std::endl;
        return false;
    }

    vars.subNumber(4);
    vars.time(std::nullopt);
    media_url = seg_temp.applyMediaTemplate(vars);
    if (media_url != "$/repId/000001/2/$Time%03d$/4/$Nonsense$/$FurtherNonsense1") {
        std::cerr << "SegmentTemplate.applyMediaTemplate() failed: expected \"$/repId/000001/2/$Time%03d$/4/$Nonsense$/$FurtherNonsense1\" got \"" << media_url << "\"" << std::endl;
        return false;
    }

    vars.time(3000);
    vars.bandwidth(std::nullopt);
    media_url = seg_temp.applyMediaTemplate(vars);
    if (media_url != "$/repId/000001/$Bandwidth$/3000/4/$Nonsense$/$FurtherNonsense1") {
        std::cerr << "SegmentTemplate.applyMediaTemplate() failed: expected \"$/repId/000001/$Bandwidth$/3000/4/$Nonsense$/$FurtherNonsense1\" got \"" << media_url << "\"" << std::endl;
        return false;
    }

    vars.bandwidth(20000);
    vars.number(std::nullopt);
    media_url = seg_temp.applyMediaTemplate(vars);
    if (media_url != "$/repId/$Number%06d$/20000/3000/4/$Nonsense$/$FurtherNonsense$Number$") {
        std::cerr << "SegmentTemplate.applyMediaTemplate() failed: expected \"$/repId/$Number%06d$/20000/3000/4/$Nonsense$/$FurtherNonsense$Number$\" got \"" << media_url << "\"" << std::endl;
        return false;
    }

    vars.number(1234);
    vars.representationId(std::nullopt);
    media_url = seg_temp.applyMediaTemplate(vars);
    if (media_url != "$/$RepresentationId$/001234/20000/3000/4/$Nonsense$/$FurtherNonsense1234") {
        std::cerr << "SegmentTemplate.applyMediaTemplate() failed: expected \"$/$RepresentationId$/001234/20000/3000/4/$Nonsense$/$FurtherNonsense1234\" got \"" << media_url << "\"" << std::endl;
        return false;
    }

    return true;
}

int main(int argc, char *argv[])
{
    int result = 0;
    static const std::vector< std::pair< std::string, std::function<bool()> > > tests = {
        { "default SegmentTemplate", test_segment_template_default },
        { "media formatting (all variables)", test_segment_template_media_template },
        { "media formatting (missing variables)", test_segment_template_vars_missing }
    };

    for (const auto &test : tests) {
        std::cout << test.first << ": ";
        if ((test.second)()) {
            std::cout << "passed";
        } else {
            result = 1;
            std::cout << "failed";
        }
        std::cout << std::endl;
    }

    return result;
}

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
